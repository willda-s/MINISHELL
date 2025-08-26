#include "../includes/minishell.h"
#include "../libft/libft.h"
#include <errno.h>
#include <fcntl.h>             // open()
#include <readline/readline.h> // readline()
#include <stdio.h>
#include <stdlib.h> // malloc, free
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h> // close(), read(), write(), dup2()

//////////////////////////////////////////////
// Générer un nom unique pour chaque heredoc
//////////////////////////////////////////////
char	*get_unique_heredoc_path(void)
{
	int		i;
	char	*path;
	int		fd;
	char	*index;

	i = 0;
	while (1)
	{
		index = ft_itoa(i);
		path = ft_strjoin("/tmp/heredoc", index);
		free(index);
		fd = open(path, O_CREAT | O_EXCL | O_WRONLY, 0644);
		if (fd != -1)
		{
			close(fd);   // fichier créé, on ferme le fd
			return (path); // on retourne le chemin unique
		}
		free(path);
		i++;
	}
}

//////////////////////////////////////////////
// Fonction pour gérer un heredoc
// Retourne le chemin du fichier temporaire créé
//////////////////////////////////////////////
char	*handle_heredoc(char *delimiter)
{
	char	*line;
	char	*heredoc_path;
	int		fd;

	heredoc_path = get_unique_heredoc_path();
	if (!heredoc_path)
		return (NULL);
	// Ouvre le fichier temporaire en écriture (trunc si existant)
	fd = open(heredoc_path, O_WRONLY | O_TRUNC);
	if (fd == -1)
	{
		perror("open heredoc");
		free(heredoc_path);
		return (NULL);
	}
	// Boucle pour lire ligne par ligne jusqu'au délimiteur
	while (1)
	{
		line = readline("> ");                     // prompt "> "
		if (!line || strcmp(line, delimiter) == 0) // TODO : RECODER STRCMP
		{
			free(line);
			break ; // fin heredoc
		}
		// Écrit la ligne + saut de ligne dans le fichier
		if (write(fd, line, ft_strlen(line)) == -1)
		{
			perror("write heredoc");
			free(line);
			break ;
		}
		if (write(fd, "\n", 1) == -1)
		{
			perror("write newline");
			free(line);
			break ;
		}
		free(line);
	}
	close(fd);
	return (heredoc_path)); // retourne le fichier temporaire créé
}

//////////////////////////////////////////////
// Construire argv depuis la liste pars (COMMANDS + ARGS)
//////////////////////////////////////////////
char	**build_argv(t_pars *pars)
{
	int		count;
	t_pars	*tmp;
	char	**argv;
	int		i;

	count = 0;
	tmp = pars;
	i = 0;
	// Compter le nombre d'éléments COMMANDS et ARGS
	while (tmp)
	{
		if ((tmp->type & COMMANDS) || (tmp->type & ARGS))
			count++;
		tmp = tmp->next;
	}
	// Allouer argv (+1 pour NULL terminal)
	argv = malloc(sizeof(char *) * (count + 1));
	if (!argv)
		return (NULL);
	tmp = pars;
	// Copier les mots dans argv
	while (tmp)
	{
		if ((tmp->type & COMMANDS) || (tmp->type & ARGS))
		{
			argv[i] = ft_strdup(tmp->word);
			i++;
		}
		tmp = tmp->next;
	}
	argv[i] = NULL; // fin de tableau argv
	return (argv);
}

//////////////////////////////////////////////
// Libérer argv
//////////////////////////////////////////////
void	free_argv(char **argv)
{
	int	i;

	i = 0;
	if (!argv)
		return ;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

//////////////////////////////////////////////
// Construire envp depuis la liste env
// (Adapter avec ta structure t_env et var KEY=VALUE)
//////////////////////////////////////////////
char	**build_envp_from_lst_env(t_env *env)
{
	int		count;
	t_env	*tmp;
	char	**envp;
	int		i;

	count = 0;
	tmp = env;
	i = 0;
	// Compter le nombre d'env pour alouer tableau de bonne taille
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return (NULL);
	tmp = env;
	// Copier les variables d'env dans envp
	while (tmp)
	{
		envp[i] = ft_strdup(tmp->value); // suppose format "KEY=VALUE"
		tmp = tmp->next;
		i++;
	}
	envp[i] = NULL; // fin tableau envp
	return (envp);
}

//////////////////////////////////////////////
// Libérer envp
//////////////////////////////////////////////
void	free_envp(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return ;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

//////////////////////////////////////////////
// Met à jour le envp dans data depuis la liste chaînée env
// Libère l'ancien envp et crée un nouveau tableau
//////////////////////////////////////////////
void	update_envp(t_data *data)
{
	if (data->envp)
		free_envp(data->envp);                      
			// libérer l'ancien tableau envp
	data->envp = build_envp_from_lst_env(data->env);
		// recréer envp à partir de la liste chaînée
}

//////////////////////////////////////////////
// Fonction d'exécution principale
// Gère les heredocs, fork/execve avec redirections
//////////////////////////////////////////////
int	exec_cmd(t_data *data)
{
	t_pars	*pars;
	t_exec	*exec_list;
	pid_t	pid;
	int		status;
	t_pars	*tmp_pars;
	char	*heredoc_file;
	int		fd;

	pars = data->pars;
	exec_list = data->exec;
	// Parcours la liste exec pour associer heredoc (file_in)
	while (exec_list)
	{
		tmp_pars = pars;
		// Cherche heredoc dans la liste pars liée
		while (tmp_pars)
		{
			if ((tmp_pars->type & HEREDOC) && tmp_pars->next
				&& tmp_pars->next->word)
			{
				heredoc_file = handle_heredoc(tmp_pars->next->word);
				if (heredoc_file)
				{
					exec_list->file_in = heredoc_file;
						// stocke le fichier temporaire
				}
			}
			tmp_pars = tmp_pars->next;
		}
		exec_list = exec_list->next;
	}
	// Avant d'exécuter, mettre à jour envp depuis la liste chaînée env
	update_envp(data);
	// Parcours exec pour fork et execve avec redirections
	exec_list = data->exec;
	while (exec_list)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			return (1);
		}
		else if (pid == 0)
		{
			// Si heredoc, rediriger stdin depuis le fichier temporaire
			if (exec_list->file_in)
			{
				fd = open(exec_list->file_in, O_RDONLY);
				if (fd == -1)
				{
					perror("open heredoc file");
					exit(EXIT_FAILURE);
				}
				dup2(fd, STDIN_FILENO);
				close(fd);
			}
			// TODO : gérer ici redirections sorties, pipes, etc.
			// Exec la commande avec argv et envp à jour
			execve(exec_list->cmd[0], exec_list->cmd, data->envp);
			perror("execve"); // si execve échoue
			exit(EXIT_FAILURE);
		}
		else
		{
			// Parent attend la fin de l'enfant
			waitpid(pid, &status, 0);
			// Supprime le fichier temporaire heredoc après usage
			if (exec_list->file_in)
				unlink(exec_list->file_in);
		}
		exec_list = exec_list->next;
	}
	return (0);
}
