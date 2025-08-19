/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 13:13:37 by mzimeris          #+#    #+#             */
/*   Updated: 2025/08/19 19:03:51 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_minishell.h"

char	**build_argv(t_command *cmd)
{
	char	**argv;
	int		i;
	int		arg_count;

	if (!cmd)
		return (NULL);
	arg_count = 0;
	while (cmd && cmd->args && cmd->args[arg_count])
		arg_count++;
	argv = malloc(sizeof(char *) * (arg_count + 2));
	if (!argv)
		return (NULL);
	argv[0] = cmd->cmd->string;
	i = 0;
	while (i < arg_count)
	{
		argv[i + 1] = cmd->args[i]->string;
		i++;
	}
	argv[arg_count + 1] = NULL;
	return (argv);
}

int	exec_child(t_env **env, t_command *command, int in_fd, int pipe_fd[2], char *outfile)
{
	int		check_result;
	char	**argv;

	if (!command || !command->cmd || !command->cmd->string)
		return (-1);
	argv = build_argv(command);
	if (!argv)
		return (-1);
	check_result = check_command(*env, command);
	if (check_result < 0)
	{
		if (in_fd > 0)
			close(in_fd);
		if (pipe_fd[0] > 0)
			close(pipe_fd[0]);
		if (pipe_fd[1] > 0)
			close(pipe_fd[1]);
	}
	handle_command_error(command, check_result);
	setup_input_redirect(in_fd);
	if (setup_output_redirect(command, pipe_fd, outfile))
	{
		exit(1);
	}
	if (!exec_builtins(command, env))
		execve(command->cmd->string, argv, (*env)->envp);
	perror("execve");
	exit(127);
}

int	fork_and_exec(t_env **env, t_command *command, int in_fd, char *outfile)
{
	int	pid;
	int	pipe_fd[2];

	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
	if (command->next != NULL && pipe(pipe_fd) < 0)
		return (handle_system_error("Pipe creation failed"), -1);
	pid = fork();
	if (pid < 0)
		return (handle_system_error("Fork failed"), -1);
	if (pid == 0)
		return (exec_child(env, command, in_fd, pipe_fd, outfile));
	(*env)->last_pid = pid;
	if (in_fd > 0)
		close(in_fd);
	if (command->next != NULL)
		return (close(pipe_fd[1]), pipe_fd[0]);
	return (0);
}

int	exec_system(t_command *command, t_env **env, char *outfile)
{
	if (!command || !command->cmd || !command->cmd->string)
		return (0);
	while (command)
	{
		if (check_command(*env, command) < 0)
			perror("command not found");
		fork_and_exec(env, command, -1, outfile);
		command = command->next;
	}
	return (-1);
}

int	exec_builtins(t_command *command, t_env **env)
{
	if (!command || !command->cmd)
		return (0);
	if (ft_strcmp(command->cmd->string, "cd") == 0)
		return (handle_cd(env, command));
	if (ft_strcmp(command->cmd->string, "pwd") == 0)
		return (handle_pwd());
	if (ft_strcmp(command->cmd->string, "echo") == 0
		&& command->args && command->args[0]
		&& ft_strcmp(command->args[0]->string, "-n") == 0)
		return (handle_echo_n(command));
	if (ft_strcmp(command->cmd->string, "export") == 0)
		return (handle_export(env, command));
	if (ft_strcmp(command->cmd->string, "unset") == 0)
		return (handle_unset(env, command));
	if (ft_strcmp(command->cmd->string, "env") == 0)
		return (handle_env(*env));
	if (ft_strcmp(command->cmd->string, "exit") == 0)
		return (handle_exit(command, env));
	return (0);
}

// int	exec(t_command *commands, t_env **env, t_token **token)
// {
// 	t_command	*current;

// 	if (!commands)
// 		return (0);
// 	current = commands;
// 	while (current)
// 	{
// 		if (!current->cmd)
// 		{
// 			printf("Error: command is NULL (should not happen)\n");
// 			current = current->next;
// 			continue ;
// 		}
// 		exec_builtins(current, env, token);
// 		current = current->next;
// 	}
// 	return (0);
// }
