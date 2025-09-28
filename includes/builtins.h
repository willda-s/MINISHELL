/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafabre <camille.fabre003@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 18:00:01 by cafabre           #+#    #+#             */
/*   Updated: 2025/09/28 21:23:16 by cafabre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int		builtin_unset(char *var, t_data *data);

int		builtin_pwd(void);

int		builtin_export(t_exec *exec, t_data *data);

int		builtin_exit(t_exec *exec, t_data *data);

int		builtin_env(t_data *data, bool export);

int		builtin_echo(t_exec *exec);

int		builtin_cd(t_exec *exec, t_data *data);

int		ensure_pwd_var(t_env **env);

void	update_pwd_vars(t_env *env, char *old_pwd);
