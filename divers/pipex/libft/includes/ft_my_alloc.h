/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_my_alloc.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 12:36:49 by mzimeris          #+#    #+#             */
/*   Updated: 2025/08/05 16:33:36 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MY_ALLOC_H
# define FT_MY_ALLOC_H

# include <stdlib.h>
# include <unistd.h>

typedef struct s_my_malloc	t_my_malloc;

typedef struct s_my_malloc
{
	size_t		size;
	void		*ptr;
	t_my_malloc	*next;
}	t_my_malloc;

typedef struct s_lalloc
{
	t_my_malloc	*head;
	size_t		total_allocated;
	size_t		total_freed;
}	t_lalloc;

void		*ft_my_malloc(t_lalloc *lalloc, size_t size);
void		ft_my_free(t_lalloc *lalloc, void *ptr);
void		*ft_my_free_all(t_lalloc *lalloc);
char		**ft_split_alloc(t_lalloc *allocator, char const *s, char c);
char		*ft_strjoin_alloc(t_lalloc *allocator, char const *s1,
				char const *s2);
t_lalloc	*init_allocator(void);

#endif /* FT_MY_ALLOC_H */