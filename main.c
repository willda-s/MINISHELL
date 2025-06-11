
#include "includes/parsing.h"
#include "libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	char *input;
	char **dst;
	t_env 	*envd;
	t_data	data;

	envd = NULL;
	init_duplicate_env(&envd, env);
	while (1)
	{
		input = readline("> ");
		if (*input)
			add_history(input);
		dst = ft_split_with_quotes(input, ' ');
		if (!dst)
			free_lst_env(&envd);
		if (init_data(&data, &envd, dst) == 1)
			free_all(&data, dst);
		init_token(&data.pars);
		handle_quotes(&data);
		print_lst_pars(data.pars);
		free_all(&data, dst);
	}
}

//TOUTES LES REMONTES D'ERREUR A REVERIFIER
//MODIFIER FREE_ENV POUR EVITER D'EXIT DEDANS
//Initialiser t_pars dans la fonction init_data ?? 
//gerer les quotes ouvert fermes + expand ce qui ya dedans