/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 00:03:28 by codespace         #+#    #+#             */
/*   Updated: 2024/12/24 00:03:32 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_death(t_philo *ph, t_sim *all)
{
	long	tmp;

	if (get_n_eat(ph) == all->nbr_of_meals)
		return (false);
	pthread_mutex_lock(&ph->sim_lock);
	tmp = get_time() - ph->last_eat;
	pthread_mutex_unlock(&ph->sim_lock);
	if (tmp > all->time_to_die)
		return (true);
	return (false);
}

bool	is_all_philos_full(t_sim *all)
{
	long	i;
	long	cnt;

	i = -1;
	cnt = 0;
	while (++i < all->philo_count)
	{
		if (get_n_eat(&all->philos[i]) == all->nbr_of_meals)
			cnt++;
	}
	if (cnt == all->philo_count)
		return (true);
	return (false);
}

int	set_finish(t_sim *all, bool set)
{
	pthread_mutex_lock(&all->sim_lock);
	all->finish = set;
	pthread_mutex_unlock(&all->sim_lock);
	return (1);
}

void	*monitor(void *arg)
{
	t_sim	*all;
	long	i;

	all = (t_sim *)arg;
	if (all->philo_count == 1)
		return (NULL);
	while (1)
	{
		i = -1;
		while (++i < all->philo_count)
		{
			if (check_death(&all->philos[i], all) && !is_finish(all)
				&& get_n_eat(&all->philos[i]) != all->nbr_of_meals)
			{
				print_status(&all->philos[i], 'd');
				return (set_finish(all, true), NULL);
			}
		}
		if (is_all_philos_full(all))
			return (NULL);
	}
	return (NULL);
}
