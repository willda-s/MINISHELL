#include "exec.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int	env_size(t_env *env)
{
	int	size;

	size = 0;
	while (env)
	{
		size++;
		env = env->next;
	}
	return (size);
}

char	**env_to_envp(t_env *env)
{
	int		size;
	char	**envp;
	char	*entry;
	int		i;

	size = env_size(env);
	envp = malloc(sizeof(char *) * (size + 1));
	i = 0;
	while (env)
	{
		entry = malloc(strlen(env->key) + strlen(env->value) + 2); // + '='+ '\0'
		if (!entry)
			return (NULL);
		strcpy(entry, env->key);
		strcat(entry, "=");
		strcat(entry, env->value);
		envp[i++] = entry;
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}
void	exec_cmd(char **argv, t_env *env)
{
	pid_t	pid;
	int		status;
	char	**envp;

	envp = env_to_envp(env);
	printf("%s", envp);
	pid = fork();
	if (pid == 0)
	{
		if (execve(argv[0], argv, envp) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
	{
		perror("fork");
	}
	else
		waitpid(pid, &status, 0);
}
t_pars	*create_node(t_type type, const char *word)
{
	t_pars	*node;

	node = malloc(sizeof(t_pars));
	if (!node)
		return (NULL);
	node->type = type;
	node->word = strdup(word);
	node->next = NULL;
	return (node);
}

void	add_pars_back(t_pars **lst, t_pars *new_node)
{
	t_pars	*tmp;

	if (!*lst)
	{
		*lst = new_node;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}

void	print_pars_list(t_pars *lst)
{
	while (lst)
	{
		printf("type: %d | word: %s\n", lst->type, lst->word);
		lst = lst->next;
	}
}

void	free_pars_list(t_pars **lst)
{
	t_pars	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		free((*lst)->word);
		free(*lst);
		*lst = tmp;
	}
}

// tester une commande
void	parsing(t_data *data, t_pars *lst)
{
	lst = NULL;
	create_new_node(lst);
	lst->type = COMMAND;
	lst->word = strdup("ls");
}
// creer liste chaine de command;
// afficher liste;
// free list;

int	main(int ac, char **av, char **envp)
{
	t_env	*env;
	t_pars	*cmds;
	int		count;
	t_pars	*tmp;
	char	**argv;
	t_pars	*tmp;
	int		i;

	(void)ac;
	(void)av;
	env = NULL;
	cmds = NULL;
	init_duplicate_env(&env, envp);
	// simulate parsing of: /bin/ls -l
	add_pars_back(&cmds, create_node(COMMAND, "/bin/ls"));
	add_pars_back(&cmds, create_node(WORD, "-l"));
	printf("=== Liste des commandes ===\n");
	print_pars_list(cmds);
	// convert t_pars to char **argv
	count = 0;
	tmp = cmds;
	while (tmp = tmp->next)
		count++;
	argv = malloc(sizeof(char *) * (count + 1));
	tmp = cmds;
	i = 0;
	while (i < count)
	{
		tmp = tmp->next;
		argv[i] = tmp->word;
		i++;
	}
	argv[count] = NULL;
	printf("=== Execution de exec_cmd ===\n");
	exec_cmd(argv, env); // ton execve fonctionne ici
	free(argv);
	free_pars_list(&cmds);
	free_lst_env(&env);
	return (0);
}

// char **env_lst_to_array(t_env *env)
// get_
// void	exec(key)
// {
// 	if (node->next->type == PIPE)
// 		handle_pipe;
// 	if (node->type == CMD)
// 		exec_cmd;
// }
// int main_exec(int ac, char **av, char **env)
// {
// 	(void)ac;
// 	(void)av;
// 	t_env *env_list = NULL;
// 	init_duplicate_env(&env_list, env);

// 	// char *argv[] = {"/bin/ls", "-l", NULL};
// 	exec_cmd(av, env_list);

// 	free_lst_env(&env_list);
// 	return (0);
// }

// int main_exec(int ac, char **av, char **env)
// {
// 	// char *input;
// 	// char **dst;
// 	t_env 	*envd;
// 	// t_data	data;

// 	envd = NULL;
// 	init_duplicate_env(&envd, env);
// 	print_lst_env(&envd);
// 	return(0);
// }