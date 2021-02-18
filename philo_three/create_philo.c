/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 22:22:18 by junkang           #+#    #+#             */
/*   Updated: 2021/02/17 22:23:56 by junkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

extern t_data	g_data;

static int		do_sleep_and_think(int philo_id)
{
	if (check_someone_die())
		return (-1);
	print_status(philo_id, SLEEP);
	new_sleep(g_data.time_to_sleep);
	if (check_someone_die())
		return (-1);
	print_status(philo_id, THINK);
	return (0);
}

static int		do_eat(int philo_id)
{
	if (check_someone_die())
		return (-1);
	if (check_someone_die() == 0)
		sem_wait(g_data.sem);
	if (check_someone_die() == 0)
		print_status(philo_id, FORK);
	if (check_someone_die() == 0)
		sem_wait(g_data.sem);
	if (check_someone_die() == 0)
	{
		print_status(philo_id, EAT);
		g_data.eat_cnt++;
	}
	g_data.last_eat = cur_time();
	new_sleep(g_data.time_to_eat);
	sem_post(g_data.sem);
	sem_post(g_data.sem);
	if (check_someone_die())
		return (-1);
	return (0);
}

void			*each_philo(void *philo_id)
{
	while (1)
	{
		if (do_eat(*(int *)philo_id) < 0)
			break ;
		if (do_sleep_and_think(*(int *)philo_id) < 0)
			break ;
	}
	return (NULL);
}

static void		check_processes(pid_t process[])
{
	int		visit[201];
	int		ret;
	int		i;
	int		status;

	memset(visit, 0, sizeof(visit));
	while (1)
	{
		i = 0;
		while (++i <= g_data.number_of_philo)
		{
			ret = waitpid(process[i], &status, WNOHANG);
			if (visit[i] || ret == 0)
				continue ;
			if (WEXITSTATUS(status) == EAT)
			{
				visit[i] = 1;
				if (++visit[0] == g_data.number_of_philo)
					return ;
			}
			else if (WEXITSTATUS(status) == DIED)
				return ;
		}
	}
}

void			create_philo(pid_t process[])
{
	int					i;
	int					philo[201];

	i = 0;
	while (++i * 2 - 1 <= g_data.number_of_philo)
	{
		philo[i * 2 - 1] = i * 2 - 1;
		process_create(&process[i * 2 - 1], each_philo, \
						(void *)&(philo[i * 2 - 1]));
	}
	new_sleep(1);
	i = 0;
	while (++i * 2 <= g_data.number_of_philo)
	{
		philo[i * 2] = i * 2;
		process_create(&process[i * 2], each_philo, \
						(void *)&(philo[i * 2]));
	}
	check_processes(process);
}
