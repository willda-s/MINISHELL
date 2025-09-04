/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: willda-s <willda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:22:27 by willda-s          #+#    #+#             */
/*   Updated: 2025/09/04 18:21:59 by willda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "libft.h"
#include "get_next_line_bonus.h"

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