
#include "../includes/parsing.h"

void print_tab(char **dst)
{
	int i;

	i = 0;
	while(dst && dst[i])
	{
		printf("dst[%d] = %s\n", i, dst[i]);
		i++;
	}
}

void free_tab(char **dst)
{
	int i;

	i = 0;
	while(dst && dst[i])
	{
		free(dst[i]);
		i++;
	}
	free(dst);
}

void free_all(t_data *data, char **dst)
{
	if (data->pars)
		free_lst_pars(&data->pars);
	if (dst)
			free_tab(dst);
	if (data->env)
		free_lst_env(&data->env);
}
