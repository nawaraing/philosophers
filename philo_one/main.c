#include "philo_one.h"

t_data	g_data;

unsigned long	cur_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	g_data.last_time = time.tv_sec * 1000000 + time.tv_usec;
	return (time.tv_sec * 1000000 + time.tv_usec);
}

int		init_data(int argc, char *argv[])
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
	g_data.is_someone_dead = 0;
	g_data.start_time = cur_time();
	g_data.last_time = g_data.start_time;
	i = 0;
	while (++i <= g_data.number_of_philo)
	{
		g_data.last_eat[i] = g_data.start_time;
		pthread_mutex_init(&(g_data.mutex[i]), NULL);
	}
	return (0);
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

int		check_someone_die(void)
{
	return (g_data.is_someone_dead);
}

int		check_i_die(int philo_id)
{
	if (g_data.last_time - g_data.last_eat[philo_id] > g_data.time_to_die)
	{
		g_data.is_someone_dead = 1;
		printf("%lu %d died\n", (cur_time() - g_data.start_time) / 1000, philo_id);
		return (1);
	}
	return (0);
}


int		do_eat(int philo_id)
{
	if (check_someone_die())
		return (-1);
	if (philo_id == 0)
		pthread_mutex_lock(&(g_data.mutex[g_data.number_of_philo - 1]));
	else
		pthread_mutex_lock(&(g_data.mutex[philo_id - 1]));
	printf("%lu %d has taken a fork\n", (cur_time() - g_data.start_time) / 1000, philo_id);
	pthread_mutex_lock(&(g_data.mutex[philo_id]));
	printf("%lu %d has taken a fork\n", (cur_time() - g_data.start_time) / 1000, philo_id);
	printf("%lu %d is eating\n", (cur_time() - g_data.start_time) / 1000, philo_id);
	g_data.last_eat[philo_id] = cur_time();
	new_sleep(g_data.time_to_eat);
	if (philo_id == 0)
		pthread_mutex_unlock(&(g_data.mutex[g_data.number_of_philo - 1]));
	else
		pthread_mutex_unlock(&(g_data.mutex[philo_id - 1]));
	pthread_mutex_unlock(&(g_data.mutex[philo_id]));
	return (0);
}

int		do_sleep_and_think(int philo_id)
{
	if (check_someone_die())
		return (-1);
	printf("%lu %d is sleeping\n", (cur_time() - g_data.start_time) / 1000, philo_id);
	new_sleep(g_data.time_to_sleep);
	printf("%lu %d is thinking\n", (cur_time() - g_data.start_time) / 1000, philo_id);
	return (0);
}

void	*each_philo(void *philo_id)
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

void	create_philo(void)
{
	int					i;
	pthread_t			thread[201];
	int					philo[201];
	int					result;

	i = 0;
	printf("number of philo: %d\n", g_data.number_of_philo);
	while (++i <= g_data.number_of_philo)
	{
		philo[i] = i;
		pthread_create(&thread[i], NULL, each_philo, (void *)&(philo[i]));
		printf("philo: %d\n", i);
	}
	i = 0;
	while (++i <= g_data.number_of_philo)
	{
		pthread_join(thread[i], (void *)&result);
	}
}

void		*work_supervisor(void *trash)
{
	int		i;

	while (1)
	{
		i = 0;
		while (++i <= g_data.number_of_philo)
		{
			if (g_data.last_eat[i] + 1000 * g_data.time_to_die < cur_time())
			{
				g_data.is_someone_dead = 1;
				return (NULL);
			}
		}
	}
	return (NULL);
}

void		create_supervisor(void)
{
	pthread_t			thread;
	int					result;

	pthread_create(&thread, NULL, work_supervisor, NULL);
	pthread_join(thread, (void *)&result);
}

int			main(int argc, char *argv[])
{
	if (init_data(argc, argv) < 0)
		return (0);
	create_supervisor();
	create_philo();
	return (0);
}