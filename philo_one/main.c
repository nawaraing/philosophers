#include "philo_one.h"

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
		pthread_mutex_init(&(g_data.mutex[i]), NULL);
	}
	return (0);
}

void			*work_supervisor(void *trash)
{
	int		i;
	int		still_hungry;

	while (1)
	{
		i = 0;
		still_hungry = 0;
		if (g_data.number_of_times_each_philo_must_eat == -1)
			still_hungry = 1;
		while (++i <= g_data.number_of_philo)
		{
			if (g_data.last_eat[i] + 1000 * g_data.time_to_die < cur_time())
			{
				print_status(i, DIED);
				g_data.is_end = 1;
				return (NULL);
			}
			if (g_data.eat_cnt[i] < g_data.number_of_times_each_philo_must_eat)
				still_hungry = 1;
		}
		if (still_hungry == 0)
		{
			g_data.is_end = 1;
			return (NULL);
		}
	}
	return (NULL);
}

void			destroy_data(void)
{
	int		i;

	i = 0;
	while (++i <= g_data.number_of_philo)
		pthread_mutex_destroy(&(g_data.mutex[i]));
}

int				main(int argc, char *argv[])
{
	pthread_t			thread;
	int					result;

	if (init_data(argc, argv) < 0)
		return (0);
	pthread_create(&thread, NULL, work_supervisor, NULL);
	create_philo();
	pthread_join(thread, NULL);
	destroy_data();
	return (0);
}