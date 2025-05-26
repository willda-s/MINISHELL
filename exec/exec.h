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
