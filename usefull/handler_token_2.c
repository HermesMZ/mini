#include "../includes/minishell.h"

int	add_redir(t_command *cmd, t_token_type type, char *filename)
{
	t_redirect	*new_redirect;

	if (!cmd || !filename)
		return (0);
	new_redirect = create_redirection(type, filename);
	if (!new_redirect)
		return (0);
	add_redirect_to_list(&(cmd->redirects), new_redirect);
	return (1);
}

int	is_redirection_token(t_token_type type)
{
	return (type == REDIR_OUT || type == REDIR_IN
		||type == REDIR_APPEND || type == HEREDOC);
}

int	handle_redirection_token(t_parsing_state *state, t_command **current_cmd)
{
	if (!*current_cmd)
		*current_cmd = create_new_command(NULL);
	*state = EXPECTING_FILE;
	return (1);
}

int	handle_pipe_token(t_parsing_state *state, t_command **current_cmd,
		t_command **commands, t_token *token)
{
	if (*current_cmd)
	{
		(*current_cmd)->pipe_out = 1;
		ft_lstadd_back_command(commands, *current_cmd);
	}
	*current_cmd = NULL;
	if (token->next && is_redirection_token(token->next->type))
		*state = EXPECTING_FILE;
	else
		*state = EXPECTING_CMD;
	return (1);
}

int	process_single_token(t_token *token, t_parsing_state *state,
		t_command **current_cmd, t_command **commands)
{
	if (token->type == WORD)
	{
		if (!handle_word_token(state, current_cmd, token, commands))
			return (0);
	}
	else if (is_redirection_token(token->type))
	{
		if (!handle_redirection_token(state, current_cmd))
			return (0);
	}
	else if (token->type == PIPE)
	{
		if (!handle_pipe_token(state, current_cmd, commands, token))
			return (0);
	}
	return (1);
}
