#include "philo.h"

static int	check_handler(const char *str, int *i, int *sign)
{
	if (!(str[*i + 1] >= '0' && str[*i + 1] <= '9'))
		return (0);
	else
	{
		if (str[*i] == '+')
			(*i)++;
		if (str[*i] == '-')
		{
			*sign = *sign * -1;
			(*i)++;
		}
	}
	return (*sign);
}

int	ft_atoi(char *str)
{
	int	i;
	int	sign;
	int	result;

	result = 0;
	i = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
		check_handler(str, &i, &sign);
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (sign * result);
}

long get_times_in_ms(void)
{
	/**
	 struct timeval
	{
		long tv_sec;   // seconds
		long tv_usec;  // micro seconds
	};
	 */
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}