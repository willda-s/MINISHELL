/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 18:00:01 by cafabre           #+#    #+#             */
/*   Updated: 2025/09/11 20:11:47 by akarapkh         ###   ########.fr       */
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
