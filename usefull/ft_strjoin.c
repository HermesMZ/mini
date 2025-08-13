#include "../includes/minishell.h"

char	*ft_strjoin(const char *str1, const char *str2)
{
	size_t	i;
	size_t	j;
	char	*tab;

	if (!str1 || !str2)
		return (NULL);
	i = 0;
	j = 0;
	tab = malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2) + 1));
	if (!tab)
		return (NULL);
	while (str1[i])
	{
		tab[i] = str1[i];
		i++;
	}
	while (str2[j])
	{
		tab[i] = str2[j];
		i++;
		j++;
	}
	tab[i] = '\0';
	return (tab);
}
