#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

//char **env_lst_to_array(t_env *env)
// get_
void	exec(node)
{
	if (node->next->type == PIPE)
		handle_pipe;
	if (node->type == CMD)
		exec;
}
int main_exec(int argc, char **argv, char **envp) 
{
	execve()
}
