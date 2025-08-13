/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:07:41 by mzimeris          #+#    #+#             */
/*   Updated: 2025/08/05 12:36:32 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include "ft_printf.h"
# include "ft_my_alloc.h"

// get_next_line
char			*get_next_line(int fd);

// simple list
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}		t_list;

void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstadd_front(t_list **lst, t_list *new);
void			ft_lstclear(t_list **lst, void (*del)(void*));
void			ft_lstdelone(t_list *lst, void (*del)(void*));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstlast(t_list *lst);
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *));
t_list			*ft_lstnew(void *content);
void			ft_lstremove_node(t_list **head, t_list *node_to_delete,
					void (*del)(void*));
int				ft_lstsize(t_list *lst);

// double list
typedef struct elem
{
	void		*content;
	struct elem	*prev;
	struct elem	*next;
}		t_elem;

typedef struct t_dblist
{
	t_elem	*first;
	t_elem	*last;
	size_t	length;
}		t_dblist;

void			ft_dlstadd_back(t_dblist *dblst, void *content);
void			ft_dlstadd_front(t_dblist *dblst, void *content);
void			ft_dlstclear(t_dblist **p_lst, void (*del)(void*));
void			ft_dlstdelone(t_elem *p_elem, void (*del)(void*));
t_dblist		*ft_dlstinit(void);
t_elem			*ft_dlstnew_elem(void *content);
int				ft_dlstsize(t_dblist **lst);

// mem
void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t count, size_t size);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memset(void *b, int c, size_t len);
void			*ft_realloc(void *ptr, size_t size);

// num
int				ft_abs(int x);
int				ft_atoi(const char *str);
long			ft_atol(const char *str);
unsigned int	ft_hextoul(const char *str);
int				ft_hextoi(const char *str);
char			*ft_itoa(int n);
char			*ft_itoa_ll(long long n);
int				ft_max(int a, int b);
int				ft_min(int a, int b);
char			*ft_ptoa(unsigned long long ptr);
char			*ft_utohex(unsigned long long n);

// printf
int				ft_printf(const char *format, ...);

// put
void			ft_putchar_fd(char c, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_putstr_fd(char *s, int fd);

// str
char			**ft_split(char const *s, char c);
void			free_splitted(char **splitted);
char			*ft_strchr(const char *s, int c);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strdup(const char *s1);
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strjoin(char const *s1, char const *s2);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t			ft_strlen(const char *s);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strndup(const char *s, size_t n);
char			*ft_strnstr(const char *haystack, const char *needle,
					size_t len);
char			*ft_strrchr(const char *s, int c);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_substr(char const *s, unsigned int start, size_t len);

// type
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
int				ft_tolower(int c);
int				ft_toupper(int c);
char			*ft_toupper_string(const char *str);

#endif /*LIBFT_H*/
