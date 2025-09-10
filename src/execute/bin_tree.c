
#include "minishell.h"

typedef struct s_cmd
{
	char	**args;
	char	*path;
}		t_cmd;

typedef struct s_btree //isso e o t_token da struct do Ximenes?
{
	char		*identifier;
	t_cmd		*cmds; //se for operador, deixar essa struct NULL
	struct s_btree	*left;
	struct s_btree	*right;
}			t_btree;

typedef struct s_head
{
	char	**envp;
	t_btree	*root;
}

void	hierarchy_btree(t_btree *node)
{
	int	status;

	if (node == NULL)
		return ;
	else if (node->identifier == COMMAND)
		execute(node);
	else if (node->identifier == PIPE)
	{	
		if (node->left->identifier == PIPE)
			hierarchy_btree(node->left);
		else if (node->left->identifier == COMMAND)
			execute_with_pipe(node);
		else
			hierarchy_btree(node->left);
	}
	else if (node->identifier == AND)
	{
		status = hierarchy_btree(node->left);
		if (status == 0) //em caso de sucesso da operacao
			hierarchy_btree(node->right);
	}
	else if (node->identifier == OR)
	{
		status = hierarchy_btree(node->left);
		if (status != 0) //em caso de failure da operacao
			hierarchy_btree(node->right);
	}
}

void	execute_with_pipe(t_btree *node)
{
	if (node->left->identifier == COMMAND)
		execute(node->left);
	if (node->right->identifier == COMMAND)
		execute(node->right);
}

int	execute(t_btree *node)
{
	pid_t	pid;
	int	status;
	int	exit_code;

	pid = child_process(node);
	waitpid(pid, &status, 0);
	free_all(NULL, node, pid, NULL);
	if (WIFEXITED(status))
		exit_code = (WEXITSTATUS(status));
	if else (WIFSIGNALED(status))	
		exit_code = WTERMSIG(status) + 128; //signal que interrompeu o processo + 128 para transformar em exit code
	//aqui add alguma coisa para guardar o ultimo exit_code e retornar usando $?
	return (exit_code); //guardar essa ultima saida como exit status do comando, usar para saida do minishell
}

pid_t	child_process(t_btree *node)
{
	int	fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		close_fd(fd);
	pid = fork();
	if (pid == -1)
		free_all(NULL, NULL, pid, fd);
	else if (pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close_fd(fd);
		execve(node->cmds.path, node->cmds.args, envp);
		free_all(NULL, node, pid, NULL);
	}
	else
	{
		dup2(fd[0], STDIN_FILENO);
		close_fd(fd);
	}
	return (pid);
}

//precisa de uma funcao para a ultima saida do output... seria a last_child
