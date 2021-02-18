/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_create.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:31:38 by junkang           #+#    #+#             */
/*   Updated: 2021/02/18 17:31:42 by junkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

extern t_data	g_data;

void			*work_supervisor(void *philo_id)
{
	int		still_hungry;

	while (1)
	{
		still_hungry = 0;
		if (g_data.number_of_times_each_philo_must_eat == -1)
			still_hungry = 1;
		if (g_data.last_eat + 1000 * g_data.time_to_die < cur_time())
		{
			print_status(*(int *)philo_id, DIED);
			g_data.is_end = DIED;
		}
		if (g_data.number_of_times_each_philo_must_eat != -1 && \
			g_data.eat_cnt >= g_data.number_of_times_each_philo_must_eat)
			g_data.is_end = EAT;
		if (g_data.is_end != 0)
			return (NULL);
	}
}

void			process_create(pid_t *process, void *(*func)(void *), void *arg)
{
	pthread_t	thread_super;
	pthread_t	thread_philo;

	if ((*process = fork()) < 0)
		printf("Fork error\n");
	if (!(*process))
	{
		pthread_create(&thread_super, NULL, work_supervisor, arg);
		pthread_create(&thread_philo, NULL, func, arg);
		pthread_detach(thread_philo);
		pthread_join(thread_super, NULL);
		sem_post(g_data.sem);
		sem_post(g_data.sem);
		exit(g_data.is_end);
	}
}
