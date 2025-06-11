
#include "env.h"

#define METACHARS "|<> \t"

typedef enum s_type
{
	NUL,
	WORD,
	NAME,
	METACHAR,
	OPERATOR,
}					t_type;

typedef struct s_pars
{
	t_type			type;
	char			*word;
	struct s_pars	*next;
}					t_pars;

typedef struct s_data
{
	t_env			*env;
	t_pars			*pars;
}					t_data;

/////////////SPLIT/////////////////////

char				**ft_split_with_quotes(char const *s, char c);

////////////LST_PARS///////////////////

int					add_back_pars(t_pars **pars);

t_pars				*ft_lstlast_pars(t_pars *pars);

int					lstsize_pars(t_pars *pars);

void				free_lst_pars(t_pars **pars);

void				print_lst_pars(t_pars *pars);

///////////INIT_DATA////////////////////

int					init_lst_pars(t_pars **pars, char **dst);

int					init_data(t_data *data, t_env **envd, char **dst);

///////////////FREE/////////////////////

void				free_all(t_data *data, char **dst);
void				free_tab(char **dst);

////////////////////TOKEN/////////////////

void				init_token(t_pars **pars);

////////////////HANDLE QUOTES AND EXPAND////////////////////

void				handle_quotes(t_data *data);
char				*get_env_value(t_env *envd, char *key);
int					is_var_start(char c);
int					is_var_char(char c);