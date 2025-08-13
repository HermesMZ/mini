/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:45:00 by mzimeris          #+#    #+#             */
/*   Updated: 2025/08/12 18:19:22 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	count_args(char *cmd)
{
	int	count;
	int	i;
	int	in_quotes;

	count = 0;
	i = 0;
	in_quotes = 0;
	while (cmd[i])
	{
		while (cmd[i] && cmd[i] == ' ')
			i++;
		if (cmd[i])
		{
			count++;
			while (cmd[i] && (cmd[i] != ' ' || in_quotes))
			{
				if (cmd[i] == '\'' && !in_quotes)
					in_quotes = 1;
				else if (cmd[i] == '\'' && in_quotes)
					in_quotes = 0;
				i++;
			}
		}
	}
	return (count);
}

static char	*extract_arg(t_lalloc *allocator, char *cmd, int *i)
{
	int		start;
	int		len;
	char	*result;

	while (cmd[*i] && cmd[*i] == ' ')
		(*i)++;
	start = *i;
	len = calculate_arg_length(cmd, start);
	result = ft_my_malloc(allocator, len + 1);
	if (!result)
		return (NULL);
	*i = start;
	copy_arg_content(cmd, i, result);
	return (result);
}

static char	**handle_empty_command(t_lalloc *allocator)
{
	char	**args;

	args = ft_my_malloc(allocator, sizeof(char *) * 2);
	if (!args)
		return (NULL);
	args[0] = ft_my_malloc(allocator, 1);
	if (!args[0])
		return (NULL);
	args[0][0] = '\0';
	args[1] = NULL;
	return (args);
}

static char	**allocate_and_fill_args(t_lalloc *allocator, char *cmd,
		int arg_count)
{
	char	**args;
	int		i;
	int		j;

	args = ft_my_malloc(allocator, sizeof(char *) * (arg_count + 1));
	if (!args)
		return (NULL);
	i = 0;
	j = 0;
	while (j < arg_count)
	{
		args[j] = extract_arg(allocator, cmd, &i);
		if (!args[j])
			return (NULL);
		j++;
	}
	args[j] = NULL;
	return (args);
}

char	**parse_command_with_quotes(t_lalloc *allocator, char *cmd)
{
	int	arg_count;

	if (!cmd || !*cmd)
		return (NULL);
	if (!validate_quotes(cmd))
		return (NULL);
	arg_count = count_args(cmd);
	if (arg_count == 0)
		return (handle_empty_command(allocator));
	return (allocate_and_fill_args(allocator, cmd, arg_count));
}
