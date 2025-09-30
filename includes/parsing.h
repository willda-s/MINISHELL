/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: willda-s <willda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:21:55 by willda-s          #+#    #+#             */
/*   Updated: 2025/09/30 03:56:23 by willda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stddef.h>
# define SYNTAX_ERR "minishell: syntax error near unexpected token `%s'\n"

# include "env.h"
# include <sys/wait.h>

typedef enum s_type
{
	NUL,
	WORD = 1,
	PIPE = 1 << 1,
	HEREDOC = 1 << 2,
	REDIR_APPEND = 1 << 3,
	REDIR_TRUNC = 1 << 4,
	REDIR_IN = 1 << 5,
	COMMANDS = 1 << 6,
	ARGS = 1 << 7,
	BUILTINS = 1 << 8,
	TARGETS = 1 << 9,
	OPEN_BRACE = 1 << 10,
	CLOSED_BRACE = 1 << 11,
	SIMPLE_QUOTE = 1 << 12,
	DOUBLE_QUOTE = 1 << 13,
	DOUBLE_PIPE = 1 << 14,
	BACK_SLASH = 1 << 15,
	REDIR = REDIR_IN | HEREDOC | REDIR_APPEND | REDIR_TRUNC,
}					t_type;

typedef struct s_redir
{
	t_type			token;
	char			*filename;
	char			*delimiter;
	struct s_redir	*next;
}					t_redir;

typedef struct s_exec
{
	char			**cmd;
	char			*path;
	int				fd_in;
	int				fd_out;
	struct s_redir	*redir;
	struct s_exec	*next;
}					t_exec;

typedef struct s_pars
{
	t_type			type;
	char			*word;
	struct s_pars	*next;
}					t_pars;

typedef struct s_data
{
	char			**dst;
	char			*input;
	int				fd_backup_in;
	int				fd_backup_out;
	t_env			*env;
	t_pars			*pars;
	t_exec			*exec;
	char			**envp;
	int				errcode;
	pid_t			pid;
	size_t			i;
	size_t			syntax_error_flag;
}					t_data;

typedef struct s_process_data
{
	char			*input;
	char			*new_input;
	int				quote_state;
	size_t			new_len;
}					t_process_data;

/////////////SPLIT_QUOTES.C/////////////////////

char				**ft_split_with_quotes(char const *s, char c);

////////////LST_UTILS_PARS.C///////////////////

int					add_back_pars(t_pars **pars);

t_pars				*ft_lstlast_pars(t_pars *pars);

void				free_lst_pars(t_pars **pars);

///////////INIT_DATA////////////////////

void				init_data(t_data *data, t_env **envd, char **dst);

///////////INIT_LST_EXEC.C && LST_UTILS_EXEC.C////////////////////

void				init_lst_exec(t_data *data);

t_exec				*ft_lstlast_exec(t_exec *exec);

int					add_back_exec(t_exec **exec);

void				free_lst_exec(t_exec **exec);

//////////INIT_REDIR///////////////

t_redir				*ft_lstlast_redir(t_redir *redir);

int					add_back_redir(t_redir **redir);

void				free_lst_redir(t_redir **redir);

///////////////FUNCTIONS_FREE.C/////////////////////

int					free_all_msg(t_data *data, int errcode, char *str);

void				free_all(t_data *data, bool quit, int errcode);

void				free_tab(char **dst);

void				free_tmpall(t_data *data);

////////////////////TYPE.C && TYPE_UTILS.C/////////////////

void				token_main(t_data *data);

void				init_token_backslash(t_pars **pars);

void				is_builtins(t_pars **tmp);

bool				is_redirection(t_pars **tmp);

////////////////EXPANDF.C, EXPANDF_UTILS.C && EXPAND_UTILS.C////////////////////

char				*get_env_value(t_env *envd, char *key);

int					is_var_char(char c);

int					max_len_in_env(t_env *env);

char				*ft_expand_word(t_data *data, char *word);

bool				is_only_dollars(char *word);

int					ft_handle_squotes(char *res, int j, char *word,
						t_data *data);

int					ft_handle_dquotes(char *res, int j, char *word,
						t_data *data);

int					expand_exec_list(t_data *data);

////////////////EXPAND_VAR.C && EXPAND_VAR_UTILS.c////////////////

int					ft_expand_var(char *res, int j, char *word, t_data *data);

int					is_expand_err(char *word, t_data *data);

int					handle_errcode(char *res, int j);

////////////////INIT_FILENAME.C//////////////////////////

void				init_lst_redir(t_exec **exec, t_pars *pars, t_data *data);

////////////////SCRATCH_NODE.C////////////////////////////

void				remove_empty_line(t_data *data);

void				init_envp(t_data *data);

////////////////VALIDATE_SYNTAX.C////////////////////////////

int					validate_syntax(t_pars *pars);

int					syntax_error(int type);

////////////////CHECK_INPUT.C////////////////////////////

int					is_command(char cmd);

int					is_space(char c);

size_t				calculate_new_len(char *input);

char				*check_input(char *input);

char				*allocate_and_initialize(char *input, size_t *new_len);

int					update_quote_state(char c, int current_state);

/////////////EXEC.C/////////////////////

void				execc(t_data *data);

bool				exec_builtins(t_exec *node, t_data *data, int fd_backup_in,
						int fd_backup_out);
////////////wait_process.c/////////////////

int					wait_process(t_data *data);

int				wait_one_process(int *flag, pid_t pid);

void	print_wait_error(int flag);

/////////////redirections_utils.c///////////////

int	open_redir_in(t_exec *node, t_data *data, const char *filename);

int	open_redir_trunc(t_exec *node, t_data *data, const char *filename);

int	open_redir_append(t_exec *node, t_data *data, const char *filename);

int	open_heredoc_in(t_exec *node, t_data *data, const char *filename);

int					dup_fd(t_exec *node, t_data *data);

void				ft_close(int *fd);

void				dup_lastcmd(t_exec *node, t_data *data);

pid_t				execfirstcmd(t_data *data, int *fd);

pid_t				execlastcmd(t_data *data, int *fd);

void				close_last_fd(t_exec *node);

void				close_first_fd(t_exec *node);

void				close_fd(t_exec *node);

char				*path_in_arg(t_exec *exec);

void	init_pipe(t_exec *node, t_data *data);

char				*find_path(t_exec *node, t_data *data);

void				close_allfd_struct(t_data *data);

int					open_all_file(t_exec *node, t_data *data);

bool				is_builtins_exec(t_exec *node);

void				handle_builtins_in_parent(t_exec *node, t_data *data);

////////////////heredoc.c////////////////////////////

void				open_heredoc_out(t_redir *redir, t_data *data);

void				handle_heredoc(t_data *data);

#endif