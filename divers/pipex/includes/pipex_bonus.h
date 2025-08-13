/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 14:13:46 by mzimeris          #+#    #+#             */
/*   Updated: 2025/08/12 17:24:50 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "pipex.h"

int		here_doc(t_pipex *pipex, int argc, char *argv[]);
int		here_doc_parse_args(t_pipex *pipex, int argc, char *argv[]);
int		setup_heredoc_redirect(t_pipex *pipex, int i, int pipe_fd[2],
			char *outfile);
int		exec_child_bonus(t_pipex *pipex, int i, int in_fd, int pipe_fd[2]);
int		exec_bonus(t_pipex *pipex, int i, int in_fd);
int		pipex_bonus(t_pipex *pipex);
int		pipex_heredoc(t_pipex *pipex);
void	here_doc_unlink(t_pipex *pipex);

#endif /* PIPEX_BONUS_H */