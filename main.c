/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 00:02:58 by codespace         #+#    #+#             */
/*   Updated: 2024/12/24 00:04:28 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_sim	data;

	if (ac != 5 && ac != 6)
		return (printf("args count incorrect\n"), 1);
	if (parse_input(ac, av, &data) == 0)
		return (printf("Error: arguments invalid\nUsage:\n"),
			printf("./philo number_of_philosophers"),
			printf(" time_to_die time_to_eat time_to_sleep"),
			printf(" [number_of_times_each_philosopher_must_eat]\n"), 1);
	data.philos = malloc(sizeof(t_philo) * data.philo_count);
	if (!data.philos)
		return (-1);
	data.forks = malloc(sizeof(pthread_mutex_t) * data.philo_count);
	if (!data.forks)
		return (free(data.philos), 1);
	if (!innit_philos(&data))
		return (clear_all(&data), 1);
	if (!start_routine(&data))
		return (clear_all(&data), 1);
	clear_all(&data);
	return (0);
}
