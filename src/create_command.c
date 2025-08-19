#include "../includes/minishell.h"

t_command	*create_new_command(t_token *token)
{
	t_command	*new_command;

	new_command = malloc(sizeof(t_command));
	if (!new_command)
		return (NULL);
	new_command->cmd = token;
	new_command->args = NULL;
	new_command->redirects = NULL;
	new_command->pipe_out = 0;
	new_command->next = NULL;
	return (new_command);
}

int	add_argument(t_command *current_command, t_token *token)
{
	int		i;
	int		j;
	t_token	**new_args;

	i = 0;
	if (current_command->args)
	{
		while (current_command->args[i])
			i++;
	}
	new_args = malloc(sizeof(t_token *) * (i + 2));
	if (!new_args)
		return (0);
	j = 0;
	while (j < i)
	{
		new_args[j] = current_command->args[j];
		j++;
	}
	new_args[i] = token;
	new_args[i + 1] = NULL;
	if (current_command->args)
		free(current_command->args);
	current_command->args = new_args;
	return (1);
}

t_redirect	*create_redirection(t_token_type type, char *filename)
{
	t_redirect	*new_redirect;

	new_redirect = malloc(sizeof(t_redirect));
	if (!new_redirect)
		return (NULL);
	new_redirect->type = type;
	new_redirect->filename = ft_strdup(filename, ft_strlen(filename), 0);
	if (!new_redirect->filename)
	{
		free(new_redirect);
		return (NULL);
	}
	new_redirect->next = NULL;
	return (new_redirect);
}

void	add_redirect_to_list(t_redirect **redirects, t_redirect *new_redirect)
{
	t_redirect	*current;

	if (!*redirects)
	{
		*redirects = new_redirect;
		return ;
	}
	current = *redirects;
	while (current->next)
		current = current->next;
	current->next = new_redirect;
}

t_command	*parse_tokens(t_token *token)
{
	t_parsing_state	state;
	t_command		*commands;
	t_command		*current_cmd;

	state = EXPECTING_CMD;
	commands = NULL;
	current_cmd = NULL;
	while (token)
	{
		if (!process_single_token(token, &state, &current_cmd, &commands))
			return (NULL);
		token = token->next;
	}
	if (current_cmd)
		ft_lstadd_back_command(&commands, current_cmd);
	return (commands);
}
