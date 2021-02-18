/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 22:21:53 by junkang           #+#    #+#             */
/*   Updated: 2021/02/17 22:22:04 by junkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

t_data			g_data;

int				init_data(int argc, char *argv[])
{
	int				i;

	if (argc != 5 && argc != 6)
		return (-1);
	g_data.number_of_philo = ft_atoi(argv[1]);
	g_data.time_to_die = ft_atoi(argv[2]);
	g_data.time_to_eat = ft_atoi(argv[3]);
	g_data.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		g_data.number_of_times_each_philo_must_eat = ft_atoi(argv[5]);
	else
		g_data.number_of_times_each_philo_must_eat = -1;
	g_data.is_end = 0;
	g_data.start_time = cur_time();
	g_data.last_time = g_data.start_time;
	i = 0;
	while (++i <= g_data.number_of_philo)
	{
		g_data.last_eat = g_data.start_time;
		g_data.eat_cnt = 0;
	}
	g_data.sem = sem_open(SEM_NAME, O_CREAT, 0644, g_data.number_of_philo);
	return (0);
}

void			destroy_data(void)
{
	sem_close(g_data.sem);
	sem_unlink(SEM_NAME);
}

void			kill_process(pid_t process[])
{
	int			i;

	i = 0;
	while (++i <= g_data.number_of_philo)
		kill(process[i], SIGKILL);
}

int				main(int argc, char *argv[])
{
	pid_t				process[201];

	destroy_data();
	if (init_data(argc, argv) < 0)
		return (0);
	create_philo(process);
	kill_process(process);
	destroy_data();
	return (0);
}
