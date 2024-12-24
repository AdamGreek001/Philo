/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 00:03:35 by codespace         #+#    #+#             */
/*   Updated: 2024/12/24 00:03:37 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_status(t_philo *ph, char msg)
{
	long	time;

	if (is_finish(ph->all))
		return (1);
	pthread_mutex_lock(&ph->all->print_lock);
	time = get_time() - ph->all->start_time;
	if (msg == 'e' && !is_finish(ph->all))
		printf("%ld\t %ld is eating\n", time, ph->index);
	else if (msg == 'f' && !is_finish(ph->all))
		printf("%ld\t %ld has taken a fork\n", time, ph->index);
	else if (msg == 's' && !is_finish(ph->all))
		printf("%ld\t %ld is sleeping\n", time, ph->index);
	else if (msg == 't' && !is_finish(ph->all))
		printf("%ld\t %ld is thinking\n", time, ph->index);
	else if (msg == 'd' && !is_finish(ph->all))
		printf("%ld\t %ld died\n", time, ph->index);
	if (msg != 'd')
		pthread_mutex_unlock(&ph->all->print_lock);
	return (1);
}

void	*one_philo(t_philo *ph, t_sim *all)
{
	pthread_mutex_lock(ph->right_fork);
	print_status(ph, 'f');
	ft_usleep(all->time_to_die, all);
	print_status(ph, 'd');
	pthread_mutex_unlock(ph->right_fork);
	set_finish(all, true);
	return (NULL);
}

int	clear_all(t_sim *all)
{
	int	i;

	i = -1;
	while (++i < all->philo_count)
	{
		pthread_mutex_destroy(&all->forks[i]);
		pthread_mutex_destroy(&all->philos[i].sim_lock);
	}
	pthread_mutex_destroy(&all->sim_lock);
	pthread_mutex_destroy(&all->print_lock);
	free(all->forks);
	free(all->philos);
	return (1);
}
