#include "philosophers.h"

long	get_current_time_ms(void)
{
	struct timeval	tv;
	long			ms;

	gettimeofday(&tv, NULL);
	ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (ms);
}

void	precise_sleep(long milliseconds)
{
	long	target_time;

	target_time = get_current_time_ms() + milliseconds;
	while (get_current_time_ms() < target_time)
		usleep(500);
}

long	get_elapsed_time(long start_time)
{
	return (get_current_time_ms() - start_time);
}

bool	is_simulation_finished(t_simulation *sim)
{
	bool	result;

	pthread_mutex_lock(&sim->sim_lock);
	result = sim->simulation_ended;
	pthread_mutex_unlock(&sim->sim_lock);
	return (result);
}

int	print_status(t_philosopher *philo, char status)
{
	long	time;

	if (is_simulation_finished(philo->sim))
		return (1);
	pthread_mutex_lock(&philo->sim->print_lock);
	time = get_elapsed_time(philo->sim->start_time);
	if (status == 'e' && !is_simulation_finished(philo->sim))
		printf("%ld\t %ld is eating\n", time, philo->id);
	else if (status == 'f' && !is_simulation_finished(philo->sim))
		printf("%ld\t %ld has taken a fork\n", time, philo->id);
	else if (status == 's' && !is_simulation_finished(philo->sim))
		printf("%ld\t %ld is sleeping\n", time, philo->id);
	else if (status == 't' && !is_simulation_finished(philo->sim))
		printf("%ld\t %ld is thinking\n", time, philo->id);
	else if (status == 'd' && !is_simulation_finished(philo->sim))
		printf("%ld\t %ld died\n", time, philo->id);
	if (status != 'd')
		pthread_mutex_unlock(&philo->sim->print_lock);
	return (1);
}