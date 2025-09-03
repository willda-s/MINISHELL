/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:21:55 by willda-s          #+#    #+#             */
/*   Updated: 2025/09/03 17:15:58 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <sys/types.h>
#include <sys/wait.h>

#define SYNTAX_ERR "minishell: syntax error near unexpected token `%s'\n"

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
	t_env			*env;
	t_pars			*pars;
	t_exec			*exec;
	char			**envp;
	char			*input;
	int				errcode;
	int				i;
}					t_data;

/////////////SPLIT_QUOTES.C/////////////////////

char				**ft_split_with_quotes(char const *s, char c);

////////////LST_UTILS_PARS.C///////////////////

int					add_back_pars(t_pars **pars);

t_pars				*ft_lstlast_pars(t_pars *pars);

void				free_lst_pars(t_pars **pars);

void				print_lst_pars(t_pars *pars);

///////////INIT_DATA////////////////////

void				init_data(t_data *data, t_env **envd, char **dst);

///////////INIT_LST_EXEC.C && LST_UTILS_EXEC.C////////////////////

void				init_lst_exec(t_data *data);

t_exec				*ft_lstlast_exec(t_exec *exec);

int					add_back_exec(t_exec **exec);

void				print_lst_exec(t_exec *exec);

void				free_lst_exec(t_exec **exec);

//////////INIT_REDIR///////////////

t_redir				*ft_lstlast_redir(t_redir *redir);

int					add_back_redir(t_redir **redir);

void				free_lst_redir(t_redir **redir);

///////////////FUNCTIONS_FREE.C/////////////////////

int					free_all_msg(t_data *data, int errcode, char *str);

int					free_all(t_data *data, int errcode);

void				free_tab(char **dst);

void				free_tmpall(t_data *data);

////////////////////TYPE.C && TYPE_UTILS.C/////////////////

void				token_main(t_data *data);

void				init_token_backslash(t_pars **pars);

void				is_builtins(t_pars **tmp);

bool				is_redirection(t_pars **tmp);

////////////////EXPANDF.C  && EXPAND_UTILS.C////////////////////

char				*get_env_value(t_env *envd, char *key);

int					is_var_char(char c);

int					ft_expand_var(char *res, int j, char *word, t_data *data);

void				expand_exec_list(t_data *data);

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

////////////////SIGNALS.C////////////////////////////

void				init_sigint(void);

/////////////EXEC.C/////////////////////

void				execc(t_data *data);

void				dup_fd(t_exec *node, t_data *data);

void				ft_close(int *fd);

void				dup_lastcmd(t_exec *node, t_data *data);

pid_t				execfirstcmd(t_data *data, int *fd);

pid_t				execlastcmd(t_data *data, int *fd);

void				close_last_fd(t_exec *node);

void				close_first_fd(t_exec *node);

void				close_fd(t_exec *node);

char				*path_in_arg(t_exec *exec);

char				*find_path(t_exec *node, t_data *data);

void				close_allfd_struct(t_data *data);

void				open_all_file(t_exec *node, t_data *data);

void				handle_heredoc(t_data *data);

int					handle_errcode(char *res, int j, t_data *data);