#include "minishell.h"

static char	*get_arrow_color(int exit_code)
{
	if (exit_code)
		return (LRED " ➜ ");
	else
		return (LGREEN " ➜ ");
}

static void	putstrbuff(const char *str, char buffer[9999], int *pos)
{
	int	i;

	i = 0;
	while (str[i])
		buffer[(*pos)++] = str[i++];
}

void	prompt_prefix(char buffer[9999])
{
	const char	*arrow = (get_arrow_color(define_exit_code(0, FALSE)));
	char		cwd[999];
	int			pos;
	int			i;

	getcwd(cwd, sizeof(cwd));
	pos = 0;
	putstrbuff(BOLD LGREEN "minishell", buffer, &pos);
	i = 0;
	while (arrow[i])
		buffer[pos++] = arrow[i++];
	putstrbuff(YELLOW "(" LMAGENTA, buffer, &pos);
	i = 0;
	while (cwd[i])
		buffer[pos++] = cwd[i++];
	putstrbuff(YELLOW ") > " RESET, buffer, &pos);
	buffer[pos] = '\0';
}
