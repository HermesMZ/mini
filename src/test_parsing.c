#include "../includes/minishell.h"

char	*get_token_type_str(t_token_type type)
{
	if (type == WORD)
		return ("WORD");
	else if (type == PIPE)
		return ("PIPE");
	else if (type == LOGICAL_OR)
		return ("LOGICAL_OR");
	else if (type == REDIR_IN)
		return ("REDIR_IN");
	else if (type == REDIR_OUT)
		return ("REDIR_OUT");
	else if (type == REDIR_APPEND)
		return ("REDIR_APPEND");
	else if (type == HEREDOC)
		return ("HEREDOC");
	else
		return ("UNKNOWN");
}

char	*get_quote_type_str(t_quote_type quote)
{
	if (quote == NO_QUOTE)
		return ("NO_QUOTE");
	else if (quote == SINGLE_QUOTE)
		return ("SINGLE_QUOTE");
	else if (quote == DOUBLE_QUOTE)
		return ("DOUBLE_QUOTE");
	else if (quote == NO_WORD)
		return ("NO_WORD");
	else
		return ("UNKNOWN");
}

char	*get_redirect_type_str(t_token_type type)
{
	if (type == REDIR_OUT)
		return (">");
	else if (type == REDIR_IN)
		return ("<");
	else if (type == REDIR_APPEND)
		return (">>");
	else if (type == HEREDOC)
		return ("<<");
	else
		return ("?");
}

void	print_redirections(t_redirect *redirects)
{
	t_redirect	*current;

	current = redirects;
	while (current)
	{
		printf("    Redirection: %s %s\n", 
			get_redirect_type_str(current->type), current->filename);
		current = current->next;
	}
}

void	print_token_arguments(t_token **args)
{
	int	i;

	if (!args || !args[0])
	{
		printf("    Args: (none)\n");
		return ;
	}
	printf("    Args:\n");
	i = 0;
	while (args[i])
	{
		printf("      [%d] \"%s\" (type:%s, quote:%s)\n", i,
			args[i]->string ? args[i]->string : "(null)",
			get_token_type_str(args[i]->type),
			get_quote_type_str(args[i]->quote_type));
		i++;
	}
}

void	print_command_details(t_command *cmd, int cmd_count)
{
	printf("\n📋 Command %d:\n", cmd_count);
	if (cmd->cmd && cmd->cmd->string)
		printf("  Command: [%s] (type:%s, quote:%s)\n", 
			cmd->cmd->string,
			get_token_type_str(cmd->cmd->type),
			get_quote_type_str(cmd->cmd->quote_type));
	else
		printf("  Command: [(null)]\n");
	print_token_arguments(cmd->args);
	if (cmd->redirects)
		print_redirections(cmd->redirects);
	else
		printf("    Redirections: (none)\n");
	printf("  Pipe out: %s\n", cmd->pipe_out ? "YES" : "NO");
}

void	test_parsing(t_token *token)
{
	t_command	*commands;
	t_command	*current;
	int			cmd_count;

	commands = parse_tokens(token);
	if (!commands)
	{
		printf("❌ Parsing failed!\n");
		return ;
	}
	printf("=== PARSING RESULTS ===\n");
	current = commands;
	cmd_count = 1;
	while (current)
	{
		print_command_details(current, cmd_count);
		current = current->next;
		cmd_count++;
	}
	printf("\n✅ Total commands: %d\n", cmd_count - 1);
	printf("=====================\n");

	free_command_chain(&commands);
}
