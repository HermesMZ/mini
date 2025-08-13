#include "../includes/minishell.h"

char	*ft_strdup(const char *s, int len_s, int i)
{
	int		j;
	char	*tab;

	tab = malloc(sizeof(char) * (len_s + 1));
	if (!tab)
		return (0);
	j = 0;
	while (j < len_s && s[i])
	{
		tab[j] = s[i];
		i++;
		j++;
	}
	tab[j] = '\0';
	return (tab);
}
