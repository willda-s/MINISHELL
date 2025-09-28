/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafabre <camille.fabre003@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 18:00:01 by cafabre           #+#    #+#             */
/*   Updated: 2025/09/25 23:54:15 by cafabre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int		builtin_unset(char *var, t_data *data);

int		builtin_pwd(void);

void	update_value(t_env *tmp, t_env *new_var);

int		parsing_export(t_exec *exec);

int		builtin_export(t_exec *exec, t_data *data);

int		builtin_exit(t_exec *exec, t_data *data);

int		builtin_env(t_data *data, bool export);

int		builtin_echo(t_exec *exec);

int		builtin_cd(t_exec *exec, t_data *data);

void	update_pwd_vars(t_env *env, char *old_pwd);

int		ensure_pwd_var(t_env **env);