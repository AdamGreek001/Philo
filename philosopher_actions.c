#include "philosophers.h"

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo;
	t_simulation	*sim;

	philo = (t_philosopher *)arg;
	sim = philo->sim;
	if (philo->id % 2 == 0 && sim->philosopher_count != 1)
		precise_sleep(sim->time_to_eat / 2);
	if (sim->philosopher_count == 1)
		return (handle_single_philosopher(philo), NULL);
	while (!is_simulation_finished(sim))
	{
		if (sim->required_meals != -1 
			&& get_meals_eaten(philo) == sim->required_meals)
			break ;
		philosopher_eat(philo);
		philosopher_sleep(philo);
		philosopher_think(philo);
	}
	return (NULL);
}

void	philosopher_eat(t_philosopher *philo)
{
	if (is_simulation_finished(philo->sim))
		return ;
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, 'f');
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, 'f');
	print_status(philo, 'e');
	
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal_time = get_current_time_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_lock);
	
	precise_sleep(philo->sim->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	philosopher_sleep(t_philosopher *philo)
{
	if (is_simulation_finished(philo->sim))
		return ;
	print_status(philo, 's');
	precise_sleep(philo->sim->time_to_sleep);
}

void	philosopher_think(t_philosopher *philo)
{
	if (is_simulation_finished(philo->sim))
		return ;
	print_status(philo, 't');
}

long	get_meals_eaten(t_philosopher *philo)
{
	long	meals;

	pthread_mutex_lock(&philo->meal_lock);
	meals = philo->meals_eaten;
	pthread_mutex_unlock(&philo->meal_lock);
	return (meals);
}