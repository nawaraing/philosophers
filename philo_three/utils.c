/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 22:22:10 by junkang           #+#    #+#             */
/*   Updated: 2021/02/17 22:26:22 by junkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

extern t_data	g_data;

int				check_someone_die(void)
{
	return (g_data.is_end);
}

void			print_status(int philo_id, int status)
{
	unsigned long		time;

	time = (cur_time() - g_data.start_time) / 1000;
	if (status == FORK)
		printf("%lu %d has taken a fork\n", time, philo_id);
	else if (status == EAT)
		printf("%lu %d is eating\n", time, philo_id);
	else if (status == SLEEP)
		printf("%lu %d is sleeping\n", time, philo_id);
	else if (status == THINK)
		printf("%lu %d is thinking\n", time, philo_id);
	else if (status == DIED)
		printf("%lu %d died\n", time, philo_id);
}

unsigned long	cur_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	g_data.last_time = time.tv_sec * 1000000 + time.tv_usec;
	return (time.tv_sec * 1000000 + time.tv_usec);
}

void			new_sleep(int usec)
{
	unsigned long	finish;
	unsigned long	cur;

	cur = cur_time();
	finish = cur + usec * 1000;
	while (finish > cur)
	{
		cur = cur_time();
		usleep(10);
	}
}

int				ft_atoi(const char *nptr)
{
	unsigned long long		res;
	int						sign;

	res = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	sign = 1;
	if (*nptr == '-')
	{
		nptr++;
		sign = -1;
	}
	else if (*nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		res = res * 10 + (*nptr - '0');
		if (res > LLONG_MAX)
			return (sign == 1 ? -1 : 0);
		nptr++;
	}
	return (sign * (int)res);
}
