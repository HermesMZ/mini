#include "../includes/minishell.h"

int	is_less_than_symbol(t_token **token, char *input, int i)
{
	t_token_data	data;

	if (input[i] == '<')
	{
		data.start = i;
		data.quote = NO_WORD;
		if (input[i + 1] && input[i + 1] == '<')
		{
			data.len = 2;
			data.type = HEREDOC;
			if (!create_token(data, input, token))
				return (0);
			return (2);
		}
		else
		{
			data.len = 1;
			data.type = REDIR_IN;
			if (!create_token(data, input, token))
				return (0);
			return (1);
		}
	}
	return (0);
}

int	is_greater_than_symbol(t_token **token, char *input, int i)
{
	t_token_data	data;

	if (input[i] == '>')
	{
		data.start = i;
		data.quote = NO_WORD;
		if (input[i + 1] && input[i + 1] == '>')
		{
			data.len = 2;
			data.type = REDIR_APPEND;
			if (!create_token(data, input, token))
				return (0);
			return (2);
		}
		else
		{
			data.len = 1;
			data.type = REDIR_OUT;
			if (!create_token(data, input, token))
				return (0);
			return (1);
		}
	}
	return (0);
}
int	is_single_quote(t_token **token, char *input, int i)
{
	t_token_data	data;
	int				start;

	if (input[i] == '\'')
	{
		start = i++;
		while (input[i] && input[i] != '\'')
			i++;
		data.start = start + 1;
		data.type = WORD;
		data.quote = SINGLE_QUOTE;
		data.len = (i - (start + 1));
		if (!create_token(data, input, token))
			return (0);
		return (i - start + 1);
	}
	return (0);
}

int	is_double_quote(t_token **token, char *input, int i)
{
	t_token_data	data;
	int				start;

	if (input[i] == '"')
	{
		start = i++;
		while (input[i] && input[i] != '"')
			i++;
		if (!input[i])
			return (printf("Error: missing closing quote\n"), 0);
		data.start = start + 1;
		data.type = WORD;
		data.quote = DOUBLE_QUOTE;
		data.len = (i - (start + 1));
		if (!create_token(data, input, token))
			return (0);
		return (i - start + 1);
	}
	return (0);
}
