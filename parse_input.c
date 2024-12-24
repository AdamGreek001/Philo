/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 00:03:03 by codespace         #+#    #+#             */
/*   Updated: 2024/12/24 00:03:08 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atoi(const char *str)
{
	int		i;
	long	s;
	long	res;
	long	tmp;

	(1) && (i = 0, s = 1, res = 0);
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	(str[i] == '+') && (i++);
	(str[i] == '-') && (i++, s = -1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		tmp = res;
		res = (res * 10) + (str[i] - 48);
		if (tmp != res / 10 && s == 1)
			return (-1);
		else if (tmp != res / 10 && s == -1)
			return (0);
		i++;
	}
	return (res * s);
}

int	get_arguments(char *s, long *set)
{
	int	i;

	i = -1;
	if (!s || !*s)
		return (0);
	while (s[++i])
	{
		if (!(s[i] >= '0' && s[i] <= '9'))
			return (0);
	}
	*set = ft_atoi(s);
	if (*set <= 0 || *set > INT_MAX)
		return (0);
	return (1);
}

int	parse_input(int ac, char **av, t_sim *data)
{
	int	i;
	int	check_it;

	i = 0;
	check_it = 0;
	check_it += get_arguments(av[1], &data->philo_count);
	check_it += get_arguments(av[2], &data->time_to_die);
	check_it += get_arguments(av[3], &data->time_to_eat);
	check_it += get_arguments(av[4], &data->time_to_sleep);
	if (ac == 6)
		check_it += get_arguments(av[5], &data->nbr_of_meals);
	else
		data->nbr_of_meals = -1;
	if (ac == 5 && check_it != 4)
		return (0);
	if (ac == 6 && check_it != 5)
		return (0);
	return (1);
}
