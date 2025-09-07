
#include "minishell.h"

typedef struct s_cmd
{
	char	**args;
	char	*path;
	char	*right_sig;
}	t_cmd;

typedef struct s_head
{
	t_cmd	*cmds;
	char	**envp;
	int	number_cmd; //numero total de cmds a ser executado
	t_pid	*pid; //array de pid dos processos executados
}	t_head;

void	execute(t_head *head)
{
//init de head precisa ter malloc(sizeof(t_pid) * head->number_cmd);
	int	i;

	i = head->number_cmd;
	while (i > 0) //i > 1 se eu usar o last_child_process
	{
		head->pid[i] = child_process(head);
		i--;
	}
	head->pid[i] = fork();
	if (head->pid[i] == 0)
//		last_child_process(head);
	wait_process(head);
}

pid_t	child_process(t_head *head)
{
	int	fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		close_fd(fd); //function to close fd
	pid = fork();
	if (pid == -1)
		close_fd(fd); //function to close fd
	else if (pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close_fd(fd); //function to close fd
		execve(head->cmds.path, head->cmds.args, head->envp);
		free_all_if_error_execve(head); //free function
	}
	else
	{
		dup2(fd[0], STDIN_FILENO);
		close_fd(fd);
	}
	return (pid);
}

void	last_child_process(t_head *head)
{
	int	fd_out;

	if (("here_doc")
		fd_out = open(outfile, O_CREAT | O_WRONLY | O_APPEND, 0644); //if here_doc, append
	else
		fd_out = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644); //else, trunc
	if (fd_out == -1)
		free_all_if_fd_errro(head); //free function
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	execve(head->cmds.path, head->cmds.args, head->envp);
}

int	wait_process(t_head *head)
{
	int	i;
	int	status;
	int	exit_code;

	i = 0;
	while (i < head->number_cmd)
	{
		waitpid(head->pid[i], &status, 0);
		if (i == (head->number_cmd - 1))
		{
			if (WIFEXITED(status))
				exit_code = WEXITSTATUS(status);
			else
				exit_code = 1; //talvez nao seja sempre 1, depende do erro, mas esse e o erro caso o processo nao termine em nada
		}
		i++;
	}
	free_all_if_error_waitprocess(head); //free function
	unlink("here_doce"); //delete all files not needed
	return (exit_code);
}
