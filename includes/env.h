
#include "../libft/libft.h"

typedef struct s_env
{
	char			*key; //HOME
	char			*value;// /home/lebroue
	struct s_env	*next; //On passe a la variable d'env d'apres 

}					t_env;

////////////LST_ENV///////////

int					add_back_env(t_env **envd);
t_env				*ft_lstlast_env(t_env *envd);
int					lstsize_env(t_env *envd);
int				free_lst_env(t_env **envd);
void				print_lst_env(t_env *envd);

//////////////////////////////

void				init_duplicate_env(t_env **envd, char **env);