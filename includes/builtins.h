/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 18:00:01 by cafabre           #+#    #+#             */
/*   Updated: 2025/09/30 18:52:51 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int		builtin_unset(t_exec *exec, t_data *data);

int		builtin_pwd(void);

int		builtin_export(t_exec *exec, t_data *data);

int		builtin_exit(t_exec *exec, t_data *data);

int		builtin_env(t_data *data, bool export);

int		builtin_echo(t_exec *exec);

int		builtin_cd(t_exec *exec, t_data *data);

int		ensure_pwd_var(t_env **env);

void	update_pwd_vars(t_env *env, char *old_pwd);
