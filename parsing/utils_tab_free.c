
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

int free_all(t_data *data, int errcode, char *str)
{
	if (data->env)
		free_lst_env(&data->env, false, 0);
	if (data->pars)
		free_lst_pars(&data->pars);
	if (data->exec)
		free_lst_exec(&data->exec);
	if (data->envp)
		free_tab(data->envp);
	if (data->dst)
		free_tab(data->dst);
	printf("%s", str);
	exit(errcode);
}