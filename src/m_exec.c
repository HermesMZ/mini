/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 13:13:37 by mzimeris          #+#    #+#             */
/*   Updated: 2025/08/13 14:12:24 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_minishell.h"

// un seul builtin pour echo
// echo -n pas de saut de ligne
int	handle_echo(char **commands)
{
	int	i;

	i = 0;
	if (ft_strcmp(commands[1], "-n") == 0)
	{
		while (commands[2][i] && commands[2][i] != '\n')
		{
			write(1, &commands[2][i], 1);
			i++;
		}
	}
	return (0);
}

int	handle_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		return (printf("%s\n", cwd));
	return (-1);
}

int	handle_exit(void)
{
	exit(0);
}

int	exec_builtins(t_command *command, t_env *env)
{
	if (!command || !command->cmd)
		return (0);
	if (ft_strcmp(command->cmd->string, "cd") == 0)
		return (handle_cd(command));
	if (ft_strcmp(command->cmd->string, "pwd") == 0)
		return (handle_pwd());
	if (ft_strcmp(command->cmd->string, "echo") == 0)
		return (handle_echo(command));
	if (ft_strcmp(command->cmd->string, "export") == 0)
		return (handle_export(env, command->args[0], command->args[1]));
	if (ft_strcmp(command->cmd->string, "unset") == 0)
		return (handle_unset(env, command->args[0]));
	if (ft_strcmp(command->cmd->string, "env") == 0)
		return (handle_env(env));
	if (ft_strcmp(command->cmd->string, "exit") == 0)
		return (handle_exit());
	printf("Commande '%s' non reconnue comme builtin\n", command->cmd->string);
	// find_and_exec(command);
	return (36);
}

// creer liste chainee de l'environnement
int	exec(t_command *commands, char **envp)
{
	t_env		*env;
	t_command	*current;

	env = extract_env(envp);
	current = commands;
	while (current)
	{
		exec_builtins(current, env);
		current = current->next;
	}
	printf("\n");
	return (36);
}

// void	run_test_commands(char **envp)
// {
// 	char	*test1[] = {"env", NULL};
// 	char	*test2[] = {"exit", NULL};


// 	printf("=== TESTS DE COMMANDES SIMPLIFIES ===\n");
// 	printf("\n--- Test 1: echo -n ---\n");
// 	exec(test1, envp);
// 	// printf("--- Test 2: exit ---\n");
// 	exec(test2, envp);
	
// 	printf("\n=== FIN DES TESTS ===\n");
// }
