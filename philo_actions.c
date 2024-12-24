/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 00:03:12 by codespace         #+#    #+#             */
/*   Updated: 2024/12/24 00:04:48 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_finish(t_sim *all)
{
	bool	tmp;

	pthread_mutex_lock(&all->sim_lock);
	tmp = all->finish;
	pthread_mutex_unlock(&all->sim_lock);
	return (tmp);
}

long	get_n_eat(t_philo *philo)
{
	long	ret;

	pthread_mutex_lock(&philo->sim_lock);
	ret = philo->meals_cnt;
	pthread_mutex_unlock(&philo->sim_lock);
	return (ret);
}

void	eat(t_philo *philo)
{
	if (is_finish(philo->all))
		return ;
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, 'f');
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, 'f');
	print_status(philo, 'e');
	ft_usleep(philo->all->time_to_eat, philo->all);
	pthread_mutex_lock(&philo->sim_lock);
	philo->last_eat = get_time();
	philo->meals_cnt++;
	pthread_mutex_unlock(&philo->sim_lock);
	pthread_mutex_unlock(philo->right_fork);
	if (philo->all->philo_count != 1)
		pthread_mutex_unlock(philo->left_fork);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_sim	*all;

	philo = (t_philo *)arg;
	all = philo->all;
	if (philo->index % 2 == 0 && all->philo_count != 1)
		ft_usleep(all->time_to_eat, philo->all);
	if (all->philo_count == 1)
		return (one_philo(philo, all));
	while (!is_finish(all))
	{
		if (all->nbr_of_meals != -1 && get_n_eat(philo) == all->nbr_of_meals)
			break ;
		eat(philo);
		if (is_finish(all))
			break ;
		print_status(philo, 's');
		ft_usleep(all->time_to_sleep, philo->all);
		print_status(philo, 't');
	}
	return (NULL);
}

int	start_routine(t_sim *all)
{
	long	i;

	i = -1;
	while (++i < all->philo_count)
	{
		if (pthread_create(&all->philos[i].philo_thrd, NULL, routine,
				(void *)&all->philos[i]) != 0)
			return (0);
	}
	if (pthread_create(&all->monitor_thread, NULL, monitor, (void *)all) != 0)
		return (0);
	i = -1;
	while (++i < all->philo_count)
	{
		if (pthread_join(all->philos[i].philo_thrd, NULL) != 0)
			return (0);
	}
	if (pthread_join(all->monitor_thread, NULL) != 0)
		return (0);
	return (1);
}
