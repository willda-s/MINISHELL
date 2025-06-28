
#include "env.h"

typedef enum s_type
{
	NUL,
	WORD = 58,
	PIPE = 1 << 1,        
	HEREDOC = 1 << 2,     
	REDIR_APPEND = 1 << 3,
	REDIR_TRUNC = 1 << 4, 
	REDIR_IN = 1 << 5,    
	COMMANDS = 1 << 9,
	ARGS = 1 << 10,
	BUILTINS = 1 << 11,
	TARGETS = 1 << 13,
	REDIR = REDIR_IN | HEREDOC | REDIR_APPEND | REDIR_TRUNC,
}					t_type;


typedef	struct s_redir
{
	t_type			token;
	char			*filename; //
	char			*delimiter;
	struct s_redir	*next;
}	t_redir;

typedef struct s_exec
{
	char			**cmd; //malloc
	char			*path; //malloc
	int				fd_in;
	int				fd_out; 
	struct s_redir	*redir;
	struct s_exec	*next;
}					t_exec;

typedef struct s_pars
{
	t_type			type;
	char			*word; //malloc
	struct s_pars	*next;
}					t_pars;

typedef struct s_data
{
	t_env			*env;
	t_pars			*pars;
	t_exec			*exec;
	char			**envp; //malloc
	int				errcode;
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

int				free_all(t_data *data, char **dst);
void				free_tab(char **dst);
void	free_lst_exec(t_exec **exec);
void	free_lst_redir(t_redir **redir);

////////////////////TOKEN/////////////////

void				token_main(t_pars **pars);

////////////////HANDLE QUOTES AND EXPAND////////////////////

void				handle_quotes(t_data *data);
char				*get_env_value(t_env *envd, char *key);
int					is_var_start(char c);
int					is_var_char(char c);

void	expand_exec_list(t_exec *exec, t_env *env);

//////////////////////////

void init_envp(t_data *data);
void print_envp(char **envp);