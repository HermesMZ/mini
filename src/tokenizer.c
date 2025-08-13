#include "../includes/minishell.h"

int	tokenizer(char *input, t_token **token, int i)
{
	int	start;
	int	ret;

	while (input[i])
	{
		while (input [i] && (input[i] == ' ' || input[i] == '\n' || input[i] == '\t'))
			i++;
		start = i;
		while (input[i] && !is_special_char(input[i]) &&
			input[i] != ' ' && input[i] != '\n' && input[i] != '\t')
			i++;
		if (i > start)
		{
			if (!add_new_token_word(start, i, token, input))
				return (ft_tokenlstclear(token), 0);
		}
		if (input[i] && is_special_char(input[i]))
		{
			ret = is_char_symbol(input, token, i);
			if (ret == 0)
				return (ft_tokenlstclear(token), 0);
			i += ret;
		}
	}
	return (1);
}

int	is_pipe(t_token **token, char *input, int i)
{
	t_token_data	data;

	data.start = i;
	data.quote = NO_WORD;
	if (input[i + 1] && input[i + 1] == '|')
	{
		data.len = 2;
		data.type = LOGICAL_OR;
		if (!create_token(data, input, token))
			return (0);
		return (2);
	}
	data.len = 1;
	data.type = PIPE;
	if (!create_token(data, input, token))
		return (0);
	return (1);
}

int	is_char_symbol(char *input, t_token **token, int i)
{
	if (input[i] == '|')
		return (is_pipe(token, input, i));
	else if (input[i] == '<')
		return (is_less_than_symbol(token, input, i));
	else if (input[i] == '>')
		return (is_greater_than_symbol(token, input, i));
	else if (input[i] == '\'')
		return (is_single_quote(token, input, i));
	else if (input[i] == '"')
		return (is_double_quote(token, input, i));
	return (1);
}

int	create_token(t_token_data data, char *input, t_token **token)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (perror("Malloc failed"), 0);
	new_token->string = ft_strdup(input, data.len, data.start);
	if (!new_token->string)
		return (perror("Malloc failed"), free(new_token), 0);
	new_token->type = data.type;
	new_token->quote_type = data.quote;
	new_token->next = NULL;
	new_token->prev = NULL;
	ft_lstadd_back(token, new_token);
	return (1);
}

int	add_new_token_word(int start, int i, t_token **token, char *input)
{
	t_token	*new_token;

	new_token = malloc(sizeof (t_token));
	if (!new_token)
		return (perror("Malloc failed"), 0);
	new_token->string = ft_strdup(input, (i - start), start);
	if (!new_token->string)
		return (perror("Malloc failed"), free(new_token), 0);
	new_token->type = WORD;
	if (start == 0)
		new_token->quote_type = NO_QUOTE;
	else if (input[start - 1] == '"')
		new_token->quote_type = DOUBLE_QUOTE;
	else if (input[start - 1] == '\'')
		new_token->quote_type = SINGLE_QUOTE;
	else
		new_token->quote_type = NO_QUOTE;
	new_token->next = NULL;
	new_token->prev = NULL;
	ft_lstadd_back(token, new_token);
	return (1);
}
