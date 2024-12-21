#include "philosophers.h"

int	validate_input(int argc, char **argv, t_simulation *sim)
{
	if (argc != 5 && argc != 6)
		return (0);
	return (parse_simulation_args(argv, sim));
}

long	safe_atoi(const char *str)
{
	long	result;
	int	i;
	int	sign;

	result = 0;
	i = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign = -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		if ((result > INT_MAX && sign == 1)
			|| (result > ((long)INT_MAX + 1) && sign == -1))
			return (-1);
		i++;
	}
	return (result * sign);
}

bool	is_valid_number(const char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (false);
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

int	parse_simulation_args(char **argv, t_simulation *sim)
{
	if (!is_valid_number(argv[1]) || !is_valid_number(argv[2])
		|| !is_valid_number(argv[3]) || !is_valid_number(argv[4]))
		return (0);
	sim->philosopher_count = safe_atoi(argv[1]);
	sim->time_to_die = safe_atoi(argv[2]);
	sim->time_to_eat = safe_atoi(argv[3]);
	sim->time_to_sleep = safe_atoi(argv[4]);
	if (argv[5])
	{
		if (!is_valid_number(argv[5]))
			return (0);
		sim->required_meals = safe_atoi(argv[5]);
	}
	else
		sim->required_meals = -1;
	if (sim->philosopher_count <= 0 || sim->time_to_die <= 0
		|| sim->time_to_eat <= 0 || sim->time_to_sleep <= 0
		|| (argv[5] && sim->required_meals <= 0))
		return (0);
	return (1);
}

void	handle_single_philosopher(t_philosopher *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, 'f');
	precise_sleep(philo->sim->time_to_die);
	print_status(philo, 'd');
	pthread_mutex_unlock(philo->right_fork);
	mark_simulation_end(philo->sim);
}
