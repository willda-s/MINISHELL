/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafabre <cafabre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 18:00:01 by cafabre           #+#    #+#             */
/*   Updated: 2025/09/11 19:03:10 by cafabre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	builtin_unset(char *var, t_env *env);

int	builtin_pwd(void);

int	builtin_export(t_exec *exec, t_data *data);

int	builtin_exit(t_exec *exec, t_data *data);

int	builtin_env(t_data *data, bool export);

int	builtin_echo(t_exec *exec);

int	builtin_cd(t_exec *exec, t_data *data);
