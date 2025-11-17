#include "minishell.h"

static char	*get_arrow_color(int exit_code)
{
	if (exit_code)
		return (LRED " ➜ ");
	else
		return (LGREEN " ➜ ");
}

void	prompt_prefix(char buffer[9999])
{
	const char	*s1 = (BOLD LCYAN "minishell");
	const char	*arrow = (get_arrow_color(define_exit_code(0, FALSE)));
	const char	*s2 = (YELLOW "(" LMAGENTA);
	const char	*s3 = (YELLOW ") > " RESET);
	char		cwd[999];
	int			pos;
	int			i;

	getcwd(cwd, sizeof(cwd));
	pos = 0;
	i = 0;
	while (s1[i])
		buffer[pos++] = s1[i++];
	i = 0;
	while (arrow[i])
		buffer[pos++] = arrow[i++];
	i = 0;
	while (s2[i])
		buffer[pos++] = s2[i++];
	i = 0;
	while (cwd[i])
		buffer[pos++] = cwd[i++];
	i = 0;
	while (s3[i])
		buffer[pos++] = s3[i++];
}
