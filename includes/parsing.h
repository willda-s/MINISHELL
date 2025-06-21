
#include "env.h"

typedef enum s_type
{
	NUL, // a garder
	WORD = 58,
	NAME = 1 << 0,
	PIPE = 1 << 1,         // a garder
	HEREDOC = 1 << 2,      // a garder
	REDIR_APPEND = 1 << 3, // a garder
	REDIR_TRUNC = 1 << 4,  // a garder
	REDIR_IN = 1 << 5,     // a garder
	SIMP_QUOTES = 1 << 6,
	DBL_QUOTES = 1 << 7,
	VAR_ENV = 1 << 8,
	COMMANDS = 1 << 9, // a garder
	ARGS = 1 << 10,    // a garder
	BUILTINS = 1 << 11,
	SYNTERR = 1 << 12,
	TARGETS = 1 << 13, // a garder
	REDIRIN = REDIR_IN | HEREDOC,
	REDIROUT = REDIR_APPEND | REDIR_TRUNC,
	REDIR = REDIRIN | REDIROUT
}					t_type;


typedef	struct s_redir
{
	t_type			token;
	char			*filename; 
	char			*delimiter;
	struct s_redir	*next;
}	t_redir;

typedef struct s_exec
{
	char			**cmd;
	char			*path; //j'y touche pas
	int				fd_in; //j'y touche pas 
	int				fd_out; //j'y touche pas 
	struct s_redir	*redir;
	struct s_exec	*next;
}					t_exec;

typedef struct s_pars
{
	t_type			type;
	char			*word;
	struct s_pars	*next;
}					t_pars;

typedef struct s_data
{
	t_env			*env; // export unset 
	t_pars			*pars;
	t_exec			*exec;
	char			**envp; //pour execve
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

///////////INIT_EXEC/////////////////////

void				init_lst_exec(t_exec **exec, t_pars *pars);

int					lstsize_exec(t_exec *exec);

t_exec				*ft_lstlast_exec(t_exec *exec);

int					add_back_exec(t_exec **exec);

void				print_lst_exec(t_exec *exec);


//////////INIT_REDIR///////////////

int	lstsize_redir(t_redir *redir);

t_redir	*ft_lstlast_redir(t_redir *redir);

int	add_back_redir(t_redir **redir);

///////////////FREE/////////////////////

void				free_all(t_data *data, char **dst);
void				free_tab(char **dst);

////////////////////TOKEN/////////////////

void				token_main(t_pars **pars);

////////////////HANDLE QUOTES AND EXPAND////////////////////

void				handle_quotes(t_data *data);
char				*get_env_value(t_env *envd, char *key);
int					is_var_start(char c);
int					is_var_char(char c);