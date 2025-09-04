/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:22:27 by willda-s          #+#    #+#             */
/*   Updated: 2025/09/04 20:17:15 by akarapkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <stdbool.h>

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;

}					t_env;

////////////ENV.C && LST_UTILS_ENV.C///////////

int					add_back_env(t_env **envd);
t_env				*ft_lstlast_env(t_env *envd);
void				free_lst_env(t_env **envd, bool ext, int errcode);
void				init_lst_env(t_env **envd, char **env);

void				print_lst_env(t_env *envd);
void				print_envp(char **envp);

#endif