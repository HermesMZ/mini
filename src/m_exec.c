/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 13:13:37 by mzimeris          #+#    #+#             */
/*   Updated: 2025/08/13 17:37:04 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_minishell.h"



int	exec(t_command *commands, t_env **env, t_token **token)
{
	t_command	*current;

	if (!commands)
		return (0);
	current = commands;
	while (current)
	{
		if (!current->cmd)
		{
			printf("Error: command is NULL (should not happen)\n");
			current = current->next;
			continue ;
		}
		exec_builtins(current, env, token);
		current = current->next;
	}
	return (0);
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
