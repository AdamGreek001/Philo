#include "philosophers.h"

void	*supervisor_routine(void *arg)
{
	t_simulation	*sim;
	long		i;

	sim = (t_simulation *)arg;
	if (sim->philosopher_count == 1)
		return (NULL);
	while (!is_simulation_finished(sim))
	{
		i = -1;
		while (++i < sim->philosopher_count)
		{
			if (check_philosopher_death(&sim->philosophers[i]))
			{
				print_status(&sim->philosophers[i], 'd');
				mark_simulation_end(sim);
				return (NULL);
			}
		}
		if (are_all_philosophers_satisfied(sim))
			return (NULL);
		precise_sleep(1);
	}
	return (NULL);
}

bool	check_philosopher_death(t_philosopher *philo)
{
	long	time_since_last_meal;

	if (get_meals_eaten(philo) == philo->sim->required_meals)
		return (false);
	pthread_mutex_lock(&philo->meal_lock);
	time_since_last_meal = get_current_time_ms() - philo->last_meal_time;
	pthread_mutex_unlock(&philo->meal_lock);
	return (time_since_last_meal > philo->sim->time_to_die);
}

bool	are_all_philosophers_satisfied(t_simulation *sim)
{
	long	i;
	long	satisfied_count;

	i = -1;
	satisfied_count = 0;
	while (++i < sim->philosopher_count)
	{
		if (get_meals_eaten(&sim->philosophers[i]) == sim->required_meals)
			satisfied_count++;
	}
	return (satisfied_count == sim->philosopher_count);
}

void	mark_simulation_end(t_simulation *sim)
{
	pthread_mutex_lock(&sim->sim_lock);
	sim->simulation_ended = true;
	pthread_mutex_unlock(&sim->sim_lock);
}

int	start_simulation(t_simulation *sim)
{
	long	i;

	i = -1;
	while (++i < sim->philosopher_count)
	{
		if (pthread_create(&sim->philosophers[i].thread, NULL,
				philosopher_routine, &sim->philosophers[i]) != 0)
			return (0);
	}
	if (pthread_create(&sim->monitor_thread, NULL,
			supervisor_routine, sim) != 0)
		return (0);
	i = -1;
	while (++i < sim->philosopher_count)
	{
		if (pthread_join(sim->philosophers[i].thread, NULL) != 0)
			return (0);
	}
	if (pthread_join(sim->monitor_thread, NULL) != 0)
		return (0);
	return (1);
}
