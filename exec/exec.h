#include "libft/libft.h"


typedef struct s_env
{
	char *key;
	char *value;
	struct s_env	*next;
}		t_env;

typedef enum s_type
{
	NUL,
	WORD,
	NAME,
	METACHAR,
	OPERATOR,

}		t_type;

typedef struct s_data
{
	t_env *env;
	t_pars *pars;

}		t_data;

typedef struct s_pars
{
	t_type 	type;
	char *word;
	struct s_pars *next;
}	t_pars;

int main_exec(int argc, char **argv, char **envp);








////////////LST_ENV///////////

int					add_back_env(t_env **envd);
t_env				*ft_lstlast_env(t_env *envd);
int					lstsize_env(t_env *envd);
int				free_lst_env(t_env **envd);
void				print_lst_env(t_env *envd);

//////////////////////////////

void				init_duplicate_env(t_env **envd, char **env);







