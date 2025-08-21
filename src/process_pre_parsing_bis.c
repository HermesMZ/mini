#include "minishell.h"

int	has_leading_pipe(char *input)
{
	int	i;

	i = 0;
	while (input[i] == ' ' || input[i] == '\t')
		i++;
	if (input[i] == '|' && input[i + 1] && input[i + 1] == '|')
	{
		printf("Minishell : syntax error near unexpected token `||'\n");
		return (1);
	}
	if (input[i] == '|')
	{
		add_history(input);
		printf("Minishell: syntax error near unexpected token `|'\n");
		return (1);
	}
	return (0);
}
