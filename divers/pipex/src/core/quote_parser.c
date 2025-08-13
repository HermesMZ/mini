/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 18:30:00 by mzimeris          #+#    #+#             */
/*   Updated: 2025/08/12 18:19:22 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	validate_quotes(char *cmd)
{
	int	i;
	int	quote_count;

	i = 0;
	quote_count = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'')
			quote_count++;
		i++;
	}
	return (quote_count % 2 == 0);
}

int	calculate_arg_length(char *cmd, int start)
{
	int	i;
	int	len;
	int	in_quotes;

	i = start;
	len = 0;
	in_quotes = 0;
	while (cmd[i] && (cmd[i] != ' ' || in_quotes))
	{
		if (cmd[i] == '\'' && !in_quotes)
			in_quotes = 1;
		else if (cmd[i] == '\'' && in_quotes)
			in_quotes = 0;
		else
			len++;
		i++;
	}
	return (len);
}

void	copy_arg_content(char *cmd, int *i, char *result)
{
	int	j;
	int	in_quotes;

	j = 0;
	in_quotes = 0;
	while (cmd[*i] && (cmd[*i] != ' ' || in_quotes))
	{
		if (cmd[*i] == '\'' && !in_quotes)
			in_quotes = 1;
		else if (cmd[*i] == '\'' && in_quotes)
			in_quotes = 0;
		else
			result[j++] = cmd[*i];
		(*i)++;
	}
	result[j] = '\0';
}
