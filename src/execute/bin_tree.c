
#include "minishell.h"

typedef struct s_cmd
{
	char	**args;
	char	*path;
	char	*right_sig; //???
}		t_cmd;

typedef struct s_btree
{
	struct s_btree	*left;
	struct s_btree	*right;
	char		*token; //nao sei se usa assim, acho que teria uma struct propria
	t_cmd		*cmds; //se for operador, deixar essa struct NULL
}			t_btree;

typedef struct s_head
{
	char	**envp;
	t_btree	*root; //*root ou **root??
}

void	hierarchy_btree(t_btree *node)
{
	int	status;

	if (node == NULL)
		return ();
	if (node->token == COMMAND)
		execute(root);
	else if (node->token == PIPE)
		execute_with_pipe(node); //execute root->left -> pipe -> execute root->right
	else if (node->token == AND)
	{
		status = hierarchy_btree(node->left);
		if (status == 0) //em caso de sucesso da operacao
			hierarchy_btree(node->right);
	}
	else if (node->token == OR)
	{
		status = hierarchy_btree(node->left);
		if (status != 0) //em caso de failure da operacao
			hierarchy_btree(node->right);
	}
}

int	execute(t_btree *node)
{
	int	status;

	status = execve(node->cmds.path, node->cmds.args, head->envp); //colocar envp dentro de cmds?
	return (status); //para caso de erro return o erro, nao sei se funciona assim
}

int	execute_with_pipe(t_btree *node)
{
	pid_t	*pid;
	int	status;

	pid = malloc(sizeof(pid_t) * 2);
	if (!pid)
		error_for_malloc(node);
	pid[0] = child_process(node->left);
	pid[1] = child_process(node->right);
	waitpid(pid[0], &status, 0);
	waitpid(pid[1], &status, 0);
	free_all_of_pid1_and_pid2(node); //function to free everything allocated for node
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1); //EXIT_FAILURE ou 1
}

pid_t	child_process(t_btree *node)
{
	int	fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		close_fd(fd); //funcao para fechar fds
	pid = fork();
	if (pid == -1)
		close_fd(fd);
	else if (pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close_fd(fd);
		execve(node->cmds.path, node->cmds.args, envp);
		free_all_if_error_execve(node);
	}
	else
	{
		dup2(fd[0], STDIN_FILENO);
		closefd(fd);
	}
	return (pid);
}

//precisa de uma funcao para a ultima saida do output... seria a last_child
