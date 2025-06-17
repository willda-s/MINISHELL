

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

#define MAX_ARGS 256

typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *next;
} 	t_env;

typedef enum s_type
{
	NUL,
	WORD,
	NAME,
	METACHAR,
	OPERATOR,
	COMMAND,
} 	t_type;

typedef struct s_lst
{
	t_type type;
	char *word;
	struct s_lst *next;
} 	t_pars;

typedef struct s_cmd 
{
	char **argv;
	char *infile;
	char *outfile;
	int append;
	int heredoc;
	struct s_cmd *next;
} 	t_cmd;

/// UTILS POUR L'EXEC///

int ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (unsigned char)*s1 - (unsigned char)*s2;
}

char *ft_strdup(const char *s)
{
	size_t len = strlen(s);
	char *dup = malloc(len + 1);
	if (!dup) return NULL;
	strcpy(dup, s);
	return (dup);
}

void add_to_argv(t_cmd *cmd, char *word)
{
	int i = 0;
	while (cmd->argv[i])
		i++;
	cmd->argv[i] = ft_strdup(word);
	cmd->argv[i+1] = NULL;
}

void add_cmd_to_list(t_cmd **cmd_list, t_cmd *cmd)
{
	t_cmd *tmp;
	if (!*cmd_list)
		*cmd_list = cmd;
	else
	{
		tmp = *cmd_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = cmd;
	}
	cmd->next = NULL;
}

// ==== Build command list from tokens ====

t_cmd *build_cmd_list(t_pars *tokens)
{
	t_cmd *cmd_list = NULL;
	t_cmd *current = NULL;

	while (tokens)
	{
		if (!current)
		{
			current = malloc(sizeof(t_cmd));
			if (!current) 
				exit(1);
			memset(current, 0, sizeof(t_cmd));
			current->argv = calloc(MAX_ARGS, sizeof(char *));
			if (!current->argv) 
				exit(1);
		}

		if (tokens->type == WORD || tokens->type == COMMAND)
			add_to_argv(current, tokens->word);
		else if (tokens->type == METACHAR && ft_strcmp(tokens->word, "<") == 0)
		{
			tokens = tokens->next;
			if (tokens)
				current->infile = ft_strdup(tokens->word);
		}
		else if (tokens->type == METACHAR && ft_strcmp(tokens->word, ">") == 0)
		{
			tokens = tokens->next;
			if (tokens)
			{
				current->outfile = ft_strdup(tokens->word);
				current->append = 0;
			}
		}
		else if (tokens->type == METACHAR && ft_strcmp(tokens->word, ">>") == 0)
		{
			tokens = tokens->next;
			if (tokens)
			{
				current->outfile = ft_strdup(tokens->word);
				current->append = 1;
			}
		}
		else if (tokens->type == METACHAR && ft_strcmp(tokens->word, "<<") == 0)
		{
			tokens = tokens->next;
			// heredoc à gérer ici (stub)
			if (tokens)
			{
				// current->infile = generate_heredoc(tokens->word);
				current->heredoc = 1;
			}
		}
		else if (tokens->type == OPERATOR && ft_strcmp(tokens->word, "|") == 0)
		{
			add_cmd_to_list(&cmd_list, current);
			current = NULL;
		}
		tokens = tokens->next;
	}
	if (current)
		add_cmd_to_list(&cmd_list, current);
	return cmd_list;
}

// ==== Redirections ====

void redirect_input(char *infile, int heredoc)
{
	int fd;
	if (heredoc)
	{
		// gestion heredoc non implémentée (stub)
		fd = open(".heredoc_tmp", O_RDONLY);
	}
	else
		fd = open(infile, O_RDONLY);
	if (fd == -1)
	{
		perror("open infile");
		exit(1);
	}
	dup2(fd, 0);
	close(fd);
}

void redirect_output(char *outfile, int append)
{
	int fd;
	if (append)
		fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("open outfile");
		exit(1);
	}
	dup2(fd, 1);
	close(fd);
}

// ==== Environnement ====

int env_len(t_env *env)
{
	int i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return i;
}

char *join_key_value(char *key, char *value)
{
	int len = strlen(key) + strlen(value) + 2;
	char *res = malloc(len);
	if (!res) return NULL;
	strcpy(res, key);
	strcat(res, "=");
	strcat(res, value);
	return res;
}

char **env_list_to_envp(t_env *env)
{
	int i = 0;
	char **envp = malloc(sizeof(char *) * (env_len(env) + 1));
	t_env *tmp = env;
	while (tmp)
	{
		envp[i++] = join_key_value(tmp->key, tmp->value);
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return envp;
}

void free_envp(char **envp)
{
	int i = 0;
	while (envp[i])
		free(envp[i++]);
	free(envp);
}

// ==== Recherche chemin exécutable ====

char *join_path(const char *path, const char *cmd)
{
	int len = strlen(path) + strlen(cmd) + 2;
	char *res = malloc(len);
	if (!res) return NULL;
	strcpy(res, path);
	strcat(res, "/");
	strcat(res, cmd);
	return res;
}

char *find_exec_path(char *cmd, t_env *env)
{
	if (!cmd)
		return NULL;
	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
		return cmd;
	char *path_env = NULL;
	while (env)
	{
		if (strcmp(env->key, "PATH") == 0)
		{
			path_env = env->value;
			break;
		}
		env = env->next;
	}
	if (!path_env)
		return cmd;

	char *paths = strdup(path_env);
	char *token = strtok(paths, ":");
	while (token)
	{
		char *full_path = join_path(token, cmd);
		if (access(full_path, X_OK) == 0)
		{
			free(paths);
			return full_path;
		}
		free(full_path);
		token = strtok(NULL, ":");
	}
	free(paths);
	return cmd;
}

// ==== Exécution ====

void exec_pipeline(t_cmd *cmd_list, t_env *env_list)
{
	int pipe_fd[2];
	int prev_fd = -1;
	pid_t pid;
	char **envp = env_list_to_envp(env_list);

	while (cmd_list)
	{
		if (cmd_list->next)
			if (pipe(pipe_fd) == -1)
			{
				perror("pipe");
				exit(1);
			}

		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(1);
		}
		if (pid == 0)
		{
			if (cmd_list->infile)
				redirect_input(cmd_list->infile, cmd_list->heredoc);
			else if (prev_fd != -1)
				dup2(prev_fd, 0);

			if (cmd_list->outfile)
				redirect_output(cmd_list->outfile, cmd_list->append);
			else if (cmd_list->next)
				dup2(pipe_fd[1], 1);

			if (prev_fd != -1)
				close(prev_fd);
			if (cmd_list->next)
			{
				close(pipe_fd[0]);
				close(pipe_fd[1]);
			}

			char *exec_path = find_exec_path(cmd_list->argv[0], env_list);
			execve(exec_path, cmd_list->argv, envp);
			perror("execve");
			exit(127);
		}
		else
		{
			if (prev_fd != -1)
				close(prev_fd);
			if (cmd_list->next)
			{
				close(pipe_fd[1]);
				prev_fd = pipe_fd[0];
			}
			waitpid(pid, NULL, 0);
			cmd_list = cmd_list->next;
		}
	}
	free_envp(envp);
}

// ==== main pour test (à adapter) ====

int main(void)
{
	// Exemple simple : ls -l | grep minishell > out.txt

	// TODO : créer ta liste de tokens t_pars * via le parser
	// Ici on simule

	t_pars p4 = {WORD, "out.txt", NULL};
	t_pars p3 = {METACHAR, ">", &p4};
	t_pars p2 = {WORD, "grep", &p3};
	t_pars p1 = {WORD, "ls", &p2};
	t_pars p0 = {WORD, "-l", &p1};

	t_cmd *cmds = build_cmd_list(&p0);

	// Simuler env
	t_env env1 = {"PATH", "/usr/bin:/bin", NULL};

	exec_pipeline(cmds, &env1);

	return 0;
}
