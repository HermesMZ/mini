/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 15:30:40 by mzimeris          #+#    #+#             */
/*   Updated: 2025/08/12 18:19:22 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <stdbool.h>
# include "libft.h"

typedef struct s_pipex
{
	char		**path;
	char		**envp;
	char		*infile;
	char		***cmds;
	char		*outfile;
	t_lalloc	*allocator;
	pid_t		last_pid;
}	t_pipex;

int		pipex(t_pipex *pipex);

t_pipex	*init_pipex(t_pipex *pipex, char *envp[]);
char	***init_cmds(t_lalloc *allocator, int cmd_count);

int		parse_args(t_pipex *pipex, int argc, char *argv[]);
char	**parse_command_with_quotes(t_lalloc *allocator, char *cmd);
int		parse_one_command(t_pipex *pipex, char *cmd, char ***cmds, int index);

/* quote_parser.c */
int		validate_quotes(char *cmd);
int		calculate_arg_length(char *cmd, int start);
void	copy_arg_content(char *cmd, int *i, char *result);

int		check_command(t_pipex *pipex, char *cmd, int index);
int		parse_one_command(t_pipex *pipex, char *cmd, char ***cmds, int index);

void	free_pipex(t_pipex *pipex);

// Execution functions
int		exec_child(t_pipex *pipex, int i, int in_fd, int pipe_fd[2]);
int		exec(t_pipex *pipex, int i, int in_fd);
int		wait_for_children(pid_t last_pid);

void	setup_input_redirect(int in_fd);
int		setup_output_redirect(t_pipex *pipex, int i, int pipe_fd[2],
			char *outfile);

// Error handling functions
void	print_command_not_found_error(const char *command);
void	print_no_such_file_error(const char *command);
void	print_permission_denied_error(const char *command);
void	handle_command_error(t_pipex *pipex, int check_result, int cmd_index);
void	handle_system_error(const char *error_msg, t_pipex *pipex);

// Debug
void	debug_print_pipex_info(t_pipex *pipex);
void	debug_argv(int argc, char *argv[]);

#endif /* PIPEX_H */