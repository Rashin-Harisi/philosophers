/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabdolho <rabdolho@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 15:32:24 by rabdolho          #+#    #+#             */
/*   Updated: 2026/04/29 15:37:29 by rabdolho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
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

long	ft_atoi(char *str)
{
	int		i;
	int		sign;
	long	result;

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

long	get_times_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	index;

	index = 0;
	while (s1[index] != '\0' && s2[index] != '\0'
		&& (s1[index] == s2[index]))
		index++;
	return ((unsigned char)s1[index] - (unsigned char)s2[index]);
}

int	is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (0);
	}
	return (1);
}

char	*create_name(t_philo *philo, char *main)
{
	char	*num;
	char	*tmp;
	char	*name;

	num = ft_itoa(philo->id);
	if (!num)
		return (NULL);
	tmp = ft_strjoin(main, '-');
	if (!tmp)
	{
		free(num);
		return (NULL);
	}
	name = ft_strjoin(tmp, num);
	free(tmp);
	free(num);
	return (name);	
}