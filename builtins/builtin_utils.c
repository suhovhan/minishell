#include "../includes/minishell.h"

int	is_alpha(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z'))
			return (1);
		else
			return (-1);
		i++;
	}
	return (0);
}
/*
char	*ft_strdup(char *s1)
{
	int		i;
	char	*dst;

	i = ft_strlen1(s1);
	dst = malloc((ft_strlen1(s1) + 1) * sizeof(char));
	i = 0;
	if (!dst || !s1)
		return (NULL);
	while (s1 && s1[i] != '\0')
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}*/
