/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: akarapkh <akarapkh@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:22:27 by willda-s          #+#    #+#             */
/*   Updated: 2025/08/27 19:52:19 by akarapkh         ###   ########.fr       */
=======
/*   By: willda-s <willda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:22:27 by willda-s          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/06/30 15:00:53 by willda-s         ###   ########.fr       */
>>>>>>> cam
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h> 
#include <stdlib.h>
#include "libft.h"
=======
/*   Updated: 2025/08/31 19:08:03 by willda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft_functions/includes/libft.h"
#include "../libft/ft_printf/includes/fd_printf.h"
#include "../libft/get_next_line/includes/get_next_line_bonus.h"
#include <stdbool.h>
#include <errno.h>
>>>>>>> parsing

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