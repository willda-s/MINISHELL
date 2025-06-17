#include "../includes/parsing.h"

static int	handle_expand(char *res, int j, const char *word, int *i, t_env *envd) //gere l'expansion de la variable d'environnement
{
    char	var[256];
    int		k;

    (*i)++;
    k = 0;
    while (word[*i] && is_var_char(word[*i]) && k < 255)
        var[k++] = word[(*i)++];
    var[k] = '\0';
    return (j + ft_strlcpy(res + j, get_env_value(envd, var), 4096 - j));
}

static int	handle_quotes_loop(t_data *data, char *word, size_t len, char *res)// boucle pour gerer les quotes et l'expansion des variables d'environnement
{
    size_t	i;
    size_t	j;
    char	quote;

    i = 0;
    j = 0;
    quote = 0;
    while (i < len)
    {
        if (!quote && (word[i] == '\'' || word[i] == '"'))
            quote = word[i++];
        else if (quote && word[i] == quote)
        {
            quote = 0;
            i++;
        }
        else if ((quote == '"' || quote == 0) && word[i] == '$'
            && is_var_start(word[i + 1]))
            j = handle_expand(res, j, word, (int *)&i, data->env);
        else
			res[j++] = word[i++];
	}
    if (quote)
        exit(2);
    res[j] = '\0';
    return (j);
}

static char	*remove_quotes_and_expand(t_data *data, char *word, size_t len) // fonction principale pour enlever les quotes et faire l'expansion des variables d'environnement
{
    char	res[4096];

    handle_quotes_loop(data, word, len, res);
    return (ft_strdup(res));
}

void	handle_quotes(t_data *data) //fonction principale
{
    t_pars *tmp;
    size_t len;
    char *new_word;

    tmp = data->pars;
    while (tmp)
    {
        if (tmp->type)
        {
            len = ft_strlen(tmp->word);
            new_word = remove_quotes_and_expand(data, tmp->word, len);
            if (new_word)
            {
                free(tmp->word);
                tmp->word = new_word;
            }
        }
        tmp = tmp->next;
    }
}

/*
Etape 1 : gerer syntaxe des quotes (quote pas fermer, quotes melangees,
	prio quotes ...)
Etape 2 : Gerer son contenu (expand ce qui est necessaire) <---- Si expand : comment modifier le contenu pour remplacer par la bonne valeur ?
le type sera forcement egal a WORD d'apres notre tokenisation.
*/

/*
TEST KO :
echo $"" = $ || expected a \n
echo $"HOME" = $HOME || expected : HOME
echo $'HOME = $HOME || expected : HOME
echo "$HO"ME = Users/williamguerreiroME || expected : ME

vu que j'enleve les quotes avant d'expand, cela devient une bonne variable d'environnement alors que non
*/