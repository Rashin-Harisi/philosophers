#include "philo.h"

int	ft_strlen(const char *str)
{
	int	count;

	count = 0;
	while (str[count] != '\0')
	{
		count++;
	}
	return (count);
}

void	copy_join_handler(char const *s, unsigned int *index_p, void *ptr)
{
	unsigned int	index;

	index = 0;
	while (s[index] != '\0')
	{
		((unsigned char *)ptr)[*index_p] = s[index];
		index++;
		(*index_p)++;
	}
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	length;
	void			*ptr;
	unsigned int	index_p;

	index_p = 0;
	length = ft_strlen(s1) + ft_strlen(s2);
	ptr = malloc((length + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	copy_join_handler(s1, &index_p, ptr);
	copy_join_handler(s2, &index_p, ptr);
	((unsigned char *)ptr)[index_p] = '\0';
	return (ptr);
}