#include "../includes/minishell.h"

int	is_special_char(char c)
{
	return (c == '<' || c == '>' || c == '|'
		|| c == '"' || c == '\'' || c == ' ');
}
