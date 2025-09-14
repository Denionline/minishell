
#include "minishell.h"

void	print(t_head *head)
{
	for (t_token *node = head->tokens; node != NULL; node = node->left) {
		printf("%s\n", node->identifier);
		if (node->right && node->right->cmd) {
			printf("%s:", node->right->cmd->path);
			for (int j = 0; node->right->cmd->args[j]; j++) {
				printf(" %s", node->right->cmd->args[j]);
			}
			printf("\n");
		}
	}
}
