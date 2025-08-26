#ifndef EXEC_H
#define EXEC_H

#include "parsing.h"
// #include "env.h"
////PATH UTILS///
void	ft_free_tab_str(char **str);

char	*envp_search(char **envp);

int	path_check(char *path, int *ret);

char	*strjoin_check_error(char *str);

//GET PATH///////

char	*get_path_in_paths_list(char **paths, int *ret, char *buffer, char *argv_cmd);

char	*get_path(char **envp, char *argv_cmd, int *ret);


//////////////////////////////////////////////////////////////////////////////////////////////

char *get_unique_heredoc_path(void);


char *handle_heredoc(char *delimiter);


void apply_redirections(t_exec *exec);


char **build_argv(t_pars *pars);

void free_argv(char **argv);

char **build_envp_from_lst_env(t_env *env);


void free_envp(char **envp);


void update_envp(t_data *data);

int exec_cmd(t_data *data);

#endif

