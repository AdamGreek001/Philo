/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-alao <eel-alao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 22:50:37 by eel-alao          #+#    #+#             */
/*   Updated: 2024/12/24 00:39:25 by eel-alao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct	s_sim t_sim;

typedef struct s_philo
{
	pthread_t			philo_thrd;
	t_sim 				*all;
	long 				meals_cnt;
	long 				last_eat;
	long 				index;
	pthread_mutex_t 	sim_lock;
	pthread_mutex_t 	*right_fork;
	pthread_mutex_t 	*left_fork;
} t_philo;

typedef struct s_sim
{
	long 				philo_count;
	long 				time_to_die;
	long 				time_to_eat;
	long 				time_to_sleep;
	long 				nbr_of_meals;
	pthread_mutex_t 	sim_lock;
	pthread_mutex_t 	print_lock;
	bool 				finish;
	t_philo 			*philos;
	pthread_mutex_t 	*forks;
	long 				start_time;
	pthread_t 			monitor_thread;
} t_sim;

int		parse_input(int ac, char **av, t_sim *data);
void	ft_usleep(long msec, t_sim *sim);
bool	is_finish(t_sim *all);
long	get_time(void);
int		print_status(t_philo *ph, char msg);
int		innit_philos(t_sim *s);
void	*routine(void *arg);
long	get_n_eat(t_philo *philo);
void 	*monitor(void *arg);
int		start_routine(t_sim *all);
int		set_finish(t_sim *all, bool set);
void	*one_philo(t_philo *ph, t_sim *all);
int		clear_all(t_sim *all);

#endif
