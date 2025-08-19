#include "../includes/minishell.h"

t_command	*handle_parsing_error(t_command **cmd, t_command *current_command)
{
	if (current_command)
		free_command(current_command);
	free_command_chain(cmd);
	return (NULL);
}

int	handle_word_expecting_cmd(t_parsing_state *state,
		t_command **current_cmd, t_token *token, t_command **commands)
{
	if (*state == EXPECTING_CMD)
	{
		if (!*current_cmd)
			*current_cmd = create_new_command(token);
		if (!*current_cmd)
		{
			handle_parsing_error(commands, *current_cmd);
			return (0);
		}
		*state = EXPECTING_CMD_OR_ARG;
	}
	return (1);
}

int	handle_word_expecting_arg(t_parsing_state *state,
		t_command **current_cmd, t_token *token, t_command **commands)
{
	if (*state == EXPECTING_CMD_OR_ARG)
	{
		if (!(*current_cmd)->cmd)
			(*current_cmd)->cmd = token;
		else if (!add_argument(*current_cmd, token))
		{
			handle_parsing_error(commands, *current_cmd);
			return (0);
		}
	}
	return (1);
}

int	handle_word_expecting_file(t_parsing_state *state,
		t_command **current_cmd, t_token *token)
{
	t_command	**commands;

	commands = NULL;
	if (*state == EXPECTING_FILE)
	{
		if (!add_redir(*current_cmd, token->prev->type, token->string))
		{
			handle_parsing_error(commands, *current_cmd);
			return (0);
		}
		*state = EXPECTING_CMD_OR_ARG;
	}
	return (1);
}

int	handle_word_token(t_parsing_state *state, t_command **current_cmd,
		t_token *token, t_command **commands)
{
	if (*state == EXPECTING_CMD)
		return (handle_word_expecting_cmd(state, current_cmd, token, commands));
	else if (*state == EXPECTING_CMD_OR_ARG)
		return (handle_word_expecting_arg(state, current_cmd, token, commands));
	else if (*state == EXPECTING_FILE)
		return (handle_word_expecting_file(state, current_cmd, token));
	return (0);
}
