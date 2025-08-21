#include "../includes/minishell.h"

int	is_token_valid(t_token *token)
{
	t_token	*next_token;

	while (token)
	{
		next_token = token->next;
		if (token -> type == PIPE || token -> type == LOGICAL_OR)
		{
			if (token -> type == LOGICAL_OR)
				return (printf("LOGICAL OR not handled\n"), 0);
			if (next_token -> type == PIPE)
				return (printf("Minishell: syntax error near unexpected token `|'\n"), 0);
		}
		if (token -> type == REDIR_IN && next_token -> type == PIPE)
			return (printf("Minishell: syntax error near unexpected token `|'"), 0);
		token = token -> next;
	}
	return (1);
}

int	is_redirection_syntax_valid(char *input)
{
	int		i;
	char	redir_char;

	i = 0;
	while (input[i])
	{
		if (input[i] == '>' || input[i] == '<')
		{
			redir_char = input[i];
			i++;
			if (input[i] == redir_char)
				i++;
			while (input[i] && (input[i] == ' ' || input[i] == '\t'))
				i++;
			if (input[i] == '\0')
				return (printf("minishell: syntax error near unexpected token `newline'\n"), 1);
			if (input[i] == '|')
				return (printf("minishell: syntax error near unexpected token `|'\n"), 1);
			if (input[i] == '>' || input[i] == '<')
			{
				if (input[i + 1] && input[i + 1] == input[i])
					return (printf("minishell: syntax error near unexpected token `%c%c'\n", input[i], input[i]), 1);
				else
					return (printf("minishell: syntax error near unexpected token `%c'\n", input[i]), 1);
			}
		}
		else
			i++;
	}
	return (0);
}

int	is_redirection_valid(t_token *token)
{
	t_token	*current;

	current = token;
	while (current)
	{
		if (current->type == REDIR_OUT || current->type == REDIR_APPEND
			|| current->type == REDIR_IN || current->type == HEREDOC)
		{
			if (!current->next)
			{
				printf("minishell: syntax error near unexpected token `newline'\n");
				return (0);
			}
			if (current->next->type != WORD)
			{
				printf("minishell: syntax error near unexpected token `%s'\n",
					get_token_symbol(current->next->type));
				return (0);
			}
		}
		current = current->next;
	}
	return (1);
}

char	*get_token_symbol(t_token_type type)
{
	if (type == PIPE)
		return ("|");
	else if (type == REDIR_OUT)
		return (">");
	else if (type == REDIR_IN)
		return ("<");
	else if (type == REDIR_APPEND)
		return (">>");
	else if (type == HEREDOC)
		return ("<<");
	else if (type == LOGICAL_OR)
		return ("||");
	return ("unknown");
}

int	process_tokens(char *input, t_token **token)
{
	if (!tokenizer(input, token, 0))
		return (0);
	if (!is_token_valid(*token))
	{
		add_history(input);
		ft_tokenlstclear(token);
		return (0);
	}
	return (1);
}
