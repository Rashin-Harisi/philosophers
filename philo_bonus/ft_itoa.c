#include "philo.h"

int	sign_count_handler(size_t *count, int *signe, int n)
{
	int	number;

	number = n;
	if (number < 0)
	{
		*signe = -(*signe);
		(*count)++;
		n = -n;
	}
	while (number != 0)
	{
		number = number / 10;
		(*count)++;
	}
	return (n);
}

void	ptr_handler(char *ptr, unsigned int *dividend,
		size_t *count, int *signe)
{
	if (*signe == -1)
		ptr[0] = '-';
	ptr[*count] = '\0';
	(*count)--;
	while (*dividend != 0)
	{
		ptr[*count] = (*dividend % 10) + '0';
		*dividend = *dividend / 10 ;
		(*count)--;
	}
}

char	*ft_itoa(int n)
{
	size_t			count;
	int				signe;
	char			*ptr;
	unsigned int	dividend;

	count = 0;
	signe = 1;
	if (n == 0)
	{
		ptr = malloc((2) * sizeof(char));
		if (ptr == NULL)
			return (NULL);
		ptr[0] = '0';
		ptr[1] = '\0';
		return (ptr);
	}
	dividend = sign_count_handler(&count, &signe, n);
	ptr = malloc((count + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	ptr_handler(ptr, &dividend, &count, &signe);
	return (ptr);
}
