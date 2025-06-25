#include "../includes/parsing.h"

static int is_valid_var(char *word, int i) {
	int k = 0;

	if (!is_var_start(word[i]))
		return 0;

	while (word[i + k] && is_var_char(word[i + k])) {
		if (word[i + k] == '"' || word[i + k] == '\'')
			return 0; // quote au milieu => invalide
		k++;
	}
	return 1;
}


static int	write_var_if_exists(char *res, int j, char *word, int *i, t_env *env)
{
    char	var[256];
    char	*val;
    int		k;

    (*i)++;
    k = 0;
    while (word[*i] && is_var_char(word[*i]) && k < 255)
        var[k++] = word[(*i)++];
    var[k] = '\0';
    val = get_env_value(env, var);
    k = 0;
    while (val && val[k])
        res[j++] = val[k++];
    return (j);
}

static int	expand_and_remove_quotes(char *res, char *word, t_env *env)
{
    int	i;
    int	j;
    char	quote;

    i = 0;
    j = 0;
    quote = 0;
    while (word[i])
    {
        if (!quote && (word[i] == '\'' || word[i] == '"'))
            quote = word[i++];
        else if (quote && word[i] == quote)
        {
            quote = 0;
            i++;
        }
        else if (word[i] == '$' && quote != '\'')
        {
            if (word[i + 1] == '\0' || word[i + 1] == '"' || word[i + 1] == '\'')
                res[j++] = word[i++];
            else if (is_valid_var(word, i + 1)) // << nouvelle condition
                j = write_var_if_exists(res, j, word, &i, env);
            else
                res[j++] = word[i++];
        }

        else
            res[j++] = word[i++];
    }
    res[j] = '\0';
    return (j);
}

char	*ft_expand(t_data *data, char *word)
{
    char	res[4096];

    expand_and_remove_quotes(res, word, data->env);
    return (ft_strdup(res));
}

void	handle_quotes(t_data *data)
{
    t_pars	*tmp;
    char	*new_word;

    tmp = data->pars;
    while (tmp)
    {
        if (tmp->word)
        {
            new_word = ft_expand(data, tmp->word);
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