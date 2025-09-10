/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafabre <cafabre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 18:00:01 by cafabre           #+#    #+#             */
/*   Updated: 2025/09/10 22:29:10 by cafabre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <limits.h>
#include <stdbool.h>

int	builtin_unset(char *var, t_env *env);
int	builtin_pwd(t_exec *exec);
int	builtin_export(t_exec *exec, t_data *data);
int	builtin_exit(t_exec *exec, t_data *data);