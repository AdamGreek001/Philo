
#include "philo.h"

long get_time(void)
{
	struct timeval t;
	long ms;

	gettimeofday(&t, NULL);
	ms = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	return (ms);
}

void ft_usleep(long msec, t_sim *sim)
{
	long target_time;

	target_time = get_time() + msec;
	while (get_time() < target_time)
	{
		if (is_finish(sim))
			break ;
		usleep(500);
	}
}

void assign_forks(t_philo *philo, pthread_mutex_t *forks, long i)
{
	philo->right_fork = &forks[i];
	if (philo->all->philo_count > 1)
	{
		if (philo->all->philo_count == i + 1)
			philo->left_fork = &forks[0];
		else
			philo->left_fork = &forks[i + 1];
	}
}

int innit_philos(t_sim *s)
{
	int i;

	i = -1;
	while (++i < s->philo_count)
	{
		s->philos[i].all = s;
		s->philos[i].index = i + 1;
		s->philos[i].last_eat = get_time();
		s->philos[i].meals_cnt = 0;
		assign_forks(&s->philos[i], s->forks, (long)i);
		if (pthread_mutex_init(&s->forks[i], NULL) != 0 || pthread_mutex_init(&s->philos[i].sim_lock, NULL) != 0)
			return (0);
	}
	if (pthread_mutex_init(&s->sim_lock, NULL) != 0 || pthread_mutex_init(&s->print_lock, NULL) != 0)
		return (0);
	s->start_time = get_time();
	return (1);
}
