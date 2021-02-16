#ifndef	PHILO_ONE_H
# define PHILO_ONE_H

# include	<pthread.h>
# include	<sys/time.h>
# include	<stdio.h>
# include	<stdlib.h>
# include	<unistd.h>
# include	<string.h>
# include	<limits.h>

typedef struct	s_data
{
	int					number_of_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					number_of_times_each_philo_must_eat;	// 없으면 -1

	int					is_someone_dead;
	unsigned long		start_time;
	unsigned long		last_time;
	unsigned long		last_eat[200];
	pthread_mutex_t		mutex[200];
}				t_data;

int				ft_atoi(const char *nptr);

#endif