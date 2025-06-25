
#include "../libft/libft.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;

}					t_env;

////////////LST_ENV///////////

int					add_back_env(t_env **envd);
t_env				*ft_lstlast_env(t_env *envd);
int					lstsize_env(t_env *envd);
int				free_lst_env(t_env **envd);
void				print_lst_env(t_env *envd);

//////////////////////////////

void				init_lst_env(t_env **envd, char **env);