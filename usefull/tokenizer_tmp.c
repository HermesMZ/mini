/*
#include "../includes/minishell.h"

t_token **input_in_token(char *input)
{
	int		i;
	t_token	**token;
	t_token *new_token;
	char	*string;

	i = 0;
	token = malloc(sizeof (t_token *));
	if (!token)
		return (perror("Malloc failed"), NULL);
	*token = NULL;
	while (input[i])
	{
		while (input[i] == ' ')
			i++;
		if (input[i])
		{
			string = input_in_string(i, input);
			new_token = tokenizer(string);
			free(string);
			if (!new_token)
				return(ft_tokenlstclear(token), NULL);
			ft_lstadd_back(token, new_token);
		}
		while (input[i] != ' ' && input[i])
			i++;
	}
	return (token);
}

t_token	*tokenizer(char *string)
{
	t_token *new_token;

	new_token = malloc (sizeof (t_token));
	if (!new_token)
		return (perror("Malloc failed"), NULL);
	new_token->string = ft_strdup(string);
	if (!new_token->string)
		return (perror("Malloc failed"), free(new_token), NULL);
	new_token->type = 1;
	new_token->next = NULL;
	return (new_token);
}

char *input_in_string(int i, char *input)
{
	int		j;
	int		nbr_letters;
	char	*string;

	nbr_letters = 0;
	while (input[i] != ' ' && input[i])
	{
		nbr_letters++;
		i++;
	}
	string = malloc(sizeof (char) * (nbr_letters + 1));
	if (!string)
		return (perror("Malloc failed"), NULL);
	i -= nbr_letters;
	j = 0;
	while (j < nbr_letters)
		string[j++] = input[i++];
	string[j] = '\0';
	return (string);
}
	int	add_new_token_var(int start, int i, t_token **token, char *input)
{
	t_token *new_token;

	new_token = malloc(sizeof (t_token));
	if (!new_token)
		return (perror("Malloc failed"), 0);
	new_token->string = ft_strdup(input, (i - start), start);
	if (!new_token->string)
		return(perror("Malloc failed"), free(new_token), 0);
	new_token->type = VAR;
	new_token->quote_type = NO_WORD;
	new_token->next = NULL;
	ft_lstadd_back(token, new_token);
	return (1);
}
int	add_new_token_symbol_duo(t_token_type symbol, int i, t_token **token, char *input)
{
	t_token *new_token;

	new_token = malloc(sizeof (t_token));
	if (!new_token)
		return (perror("Malloc failed"), 0);
	new_token->string = ft_strdup(input, 2, i);
	if (!new_token->string)
		return(perror("Malloc failed"), free(new_token), 0);
	new_token->type = symbol;
	new_token->quote_type = NO_WORD;
	new_token->next = NULL;
	ft_lstadd_back(token, new_token);
	return (1);
}
int	add_new_token_symbol_solo(t_token_type symbol, int i, t_token **token, char *input)
{
	t_token *new_token;

	new_token = malloc(sizeof (t_token));
	if (!new_token)
		return (perror("Malloc failed"), 0);
	new_token->string = ft_strdup(input, 1, i);
	if (!new_token->string)
		return(perror("Malloc failed"), free(new_token), 0);
	new_token->type = symbol;
	new_token->quote_type = NO_WORD;
	new_token->next = NULL;
	ft_lstadd_back(token, new_token);
	return (1);
}
int	is_dollard(t_token **token, char *input, int i)
{
	t_token_data	data;
	int				start;

	if (input[i] == '$')
	{
		start = i++;
		if (input[i] == '?')
			i++;
		else if (ft_isalpha(input[i]) || input[i] == '_')
		{
			while (ft_isalnum(input[i]) || input[i] == '_')
				i++;
		}
		else if (ft_isdigit(input[i]))
			i++;
		data.start = start;
		data.len = i - start;
		data.type = VAR;
		data.quote = NO_WORD;
		if (!create_token(data, input, token))
			return (0);
		return (i - start);
	}
	return (0);
}*/