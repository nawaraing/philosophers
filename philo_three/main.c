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
		g_data.last_eat[i] = g_data.start_time;
		g_data.eat_cnt[i] = 0;
	}
	g_data.sem = sem_open(SEM_NAME, O_CREAT, 0644, g_data.number_of_philo);
	return (0);
}

void			*work_supervisor(void *trash)
{
	int		i;
	int		still_hungry;

	trash = NULL;
	while (1)
	{
		still_hungry = 0;
		if (g_data.number_of_times_each_philo_must_eat == -1)
			still_hungry = 1;
		i = 0;
		while (++i <= g_data.number_of_philo)
		{
			if (g_data.last_eat[i] + 1000 * g_data.time_to_die < cur_time())
			{
				print_status(i, DIED);
				g_data.is_end = 1;
			}
			if (g_data.eat_cnt[i] < g_data.number_of_times_each_philo_must_eat)
				still_hungry = 1;
		}
		if (still_hungry == 0)
			g_data.is_end = 1;
		if (g_data.is_end)
			return (NULL);
	}
}

void			destroy_data(void)
{
	sem_close(g_data.sem);
	sem_unlink(SEM_NAME);
}

void			process_create(pid_t *process, void *(*func) (void *), void *arg)
{
	arg = NULL;
	*process = fork();
	if (!(*process))
	{
		func(arg);
		exit(0);
	}
}

int				main(int argc, char *argv[])
{
	pid_t			process;
	int				status;

	destroy_data();
	if (init_data(argc, argv) < 0)
		return (0);
	process_create(&process, work_supervisor, NULL);
	create_philo();
	waitpid(process, &status, 0);
	destroy_data();
	return (0);
}
