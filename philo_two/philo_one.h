#ifndef	PHILO_ONE_H
# define PHILO_ONE_H

# include	<pthread.h>
# include	<semaphore.h>
# include	<sys/time.h>
# include	<stdio.h>
# include	<stdlib.h>
# include	<unistd.h>
# include	<string.h>
# include	<limits.h>

# define 	FORK	1
# define	EAT		2
# define	SLEEP	3
# define	THINK	4
# define	DIED	5

typedef struct	s_data
{
	int					number_of_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					number_of_times_each_philo_must_eat;	// 없으면 -1

	int					is_end;
	unsigned long		start_time;
	unsigned long		last_time;
	unsigned long		last_eat[200];
	int					eat_cnt[200];
	pthread_mutex_t		mutex[200];
}				t_data;

void			create_philo(void);

int				check_someone_die(void);
void			print_status(int philo_id, int status);
unsigned long	cur_time(void);
int				ft_atoi(const char *nptr);
void			new_sleep(int usec);

#endif