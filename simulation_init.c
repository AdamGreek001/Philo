#include "philosophers.h"

int	init_simulation(int argc, char **argv, t_simulation *sim)
{
	if (!validate_input(argc, argv, sim))
		return (0);
	sim->philosophers = malloc(sizeof(t_philosopher) * sim->philosopher_count);
	if (!sim->philosophers)
		return (0);
	sim->forks = malloc(sizeof(pthread_mutex_t) * sim->philosopher_count);
	if (!sim->forks)
	{
		free(sim->philosophers);
		return (0);
	}
	if (!init_mutexes(sim) || !create_philosophers(sim))
	{
		cleanup_simulation(sim);
		return (0);
	}
	sim->simulation_ended = false;
	sim->start_time = get_current_time_ms();
	return (1);
}

int	create_philosophers(t_simulation *sim)
{
	int	i;

	i = -1;
	while (++i < sim->philosopher_count)
	{
		sim->philosophers[i].sim = sim;
		sim->philosophers[i].id = i + 1;
		sim->philosophers[i].last_meal_time = get_current_time_ms();
		sim->philosophers[i].meals_eaten = 0;
		assign_forks(&sim->philosophers[i], sim->forks, (long)i);
		if (pthread_mutex_init(&sim->forks[i], NULL) != 0
			|| pthread_mutex_init(&sim->philosophers[i].meal_lock, NULL) != 0)
			return (0);
	}
	return (1);
}

void	assign_forks(t_philosopher *philo, pthread_mutex_t *forks, long index)
{
	philo->right_fork = &forks[index];
	if (philo->sim->philosopher_count > 1)
	{
		if (index + 1 == philo->sim->philosopher_count)
			philo->left_fork = &forks[0];
		else
			philo->left_fork = &forks[index + 1];
	}
}

int	init_mutexes(t_simulation *sim)
{
	if (pthread_mutex_init(&sim->sim_lock, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&sim->print_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&sim->sim_lock);
		return (0);
	}
	return (1);
}

void	cleanup_simulation(t_simulation *sim)
{
	int	i;

	i = -1;
	while (++i < sim->philosopher_count)
	{
		pthread_mutex_destroy(&sim->forks[i]);
		pthread_mutex_destroy(&sim->philosophers[i].meal_lock);
	}
	pthread_mutex_destroy(&sim->sim_lock);
	pthread_mutex_destroy(&sim->print_lock);
	free(sim->forks);
	free(sim->philosophers);
}