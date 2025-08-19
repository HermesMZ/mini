#include "../includes/minishell.h"

void	free_redirections(t_redirect *redirects)
{
	t_redirect	*current;
	t_redirect	*next;

	current = redirects;
	while (current)
	{
		next = current->next;
		if (current->filename)
			free(current->filename);
		free(current);
		current = next;
	}
}

void	free_token_array(t_token **args)
{
	if (!args)
		return ;
	free(args);
}

void	free_command(t_command *cmd)
{
	if (!cmd)
		return ;
	if (cmd->args)
		free_token_array(cmd->args);
	if (cmd->redirects)
		free_redirections(cmd->redirects);
	free(cmd);
}

void	free_command_chain(t_command **commands)
{
	t_command	*current;
	t_command	*next;

	if (!commands || !*commands)
		return ;
	current = *commands;
	while (current)
	{
		next = current->next;
		free_command(current);
		current = next;
	}
	*commands = NULL;
}
