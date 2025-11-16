#include "minishell.h"

void	get_prompt_prefix(char buffer[999])
{
	const char	*s1 = (GREEN "➜ " CYAN "minishell " YELLOW "(" MAGENTA);
	const char	*s2 = (YELLOW ") >" RESET);
	char		cwd[2041];
	int			pos;
	int			i;

	getcwd(cwd, sizeof(cwd));
	pos = 0;
	i = 0;
	while (s1[i])
		buffer[pos++] = s1[i++];
	i = 0;
	while (cwd[i])
		buffer[pos++] = cwd[i++];
	i = 0;
	while (s2[i])
		buffer[pos++] = s2[i++];
	buffer[pos] = '\0';
}
