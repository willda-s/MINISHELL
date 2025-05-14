
#include "env.h"

typedef enum s_type
{
	WORD,
	COMMANDS,
	ARGUMENT,
	REDIRECTION,
	PIPE,
	SMPL_QUOTE,
	DBL_QUOTE,
	VAR_ENV,
	CARAC_SPE
}			t_type;

typedef struct s_pars
{
	t_type	type;
	char	*value;
	struct s_pars	*next;
}			t_pars;

typedef struct s_data
{
	t_env *env;
	t_pars *pars;
}		t_data;