/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_alloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 14:00:00 by mzimeris          #+#    #+#             */
/*   Updated: 2025/08/05 15:45:36 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_my_alloc.h"
#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static char	*create_word(t_lalloc *allocator, char const *s, int start, int end)
{
	char	*word;
	int		i;

	word = ft_my_malloc(allocator, (end - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	i = 0;
	while (start < end)
	{
		word[i] = s[start];
		i++;
		start++;
	}
	word[i] = '\0';
	return (word);
}

static int	skip_separators_and_find_word(char const *s, int *i, char c)
{
	int	start;

	while (s[*i] && s[*i] == c)
		(*i)++;
	start = *i;
	while (s[*i] && s[*i] != c)
		(*i)++;
	return (start);
}

static char	**fill_words(t_lalloc *allocator, char const *s, char c,
		int word_count)
{
	char	**result;
	int		i;
	int		start;
	int		word_index;

	result = ft_my_malloc(allocator, (word_count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	word_index = 0;
	while (s[i] && word_index < word_count)
	{
		start = skip_separators_and_find_word(s, &i, c);
		if (i > start)
		{
			result[word_index] = create_word(allocator, s, start, i);
			if (!result[word_index])
				return (NULL);
			word_index++;
		}
	}
	result[word_index] = NULL;
	return (result);
}

char	**ft_split_alloc(t_lalloc *allocator, char const *s, char c)
{
	int	word_count;

	if (!s || !allocator)
		return (NULL);
	word_count = count_words(s, c);
	return (fill_words(allocator, s, c, word_count));
}
