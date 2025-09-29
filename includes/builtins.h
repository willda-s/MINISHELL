/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: willda-s <willda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 18:00:01 by cafabre           #+#    #+#             */
/*   Updated: 2025/09/30 00:14:01 by willda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int		builtin_unset(t_exec *exec, t_data *data);

int		builtin_pwd(void);

int		builtin_export(t_exec *exec, t_data *data);

int		builtin_exit(t_exec *exec, t_data *data);

int		builtin_env(t_data *data, bool export);

int		builtin_echo(t_exec *exec);

int	builtin_cd(t_exec *exec, t_data *data);


/////////////////cd_utils.c//////////////////
int	    set_node(t_env *node, const char *key, const char *value);

int	    add_env_var(t_env **env, const char *key, const char *value);

int     handle_no_pwd(int has_pwd, int error_control, t_env **env);

int	    ensure_pwd_var(t_env **env);

void	update_pwd_vars(t_env *env, char *old_pwd);
