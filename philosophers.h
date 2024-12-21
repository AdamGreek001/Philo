#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_simulation	t_simulation;

typedef struct s_philosopher
{
	pthread_t		thread;
	t_simulation	*sim;
	long			meals_eaten;
	long			last_meal_time;
	long			id;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
}	t_philosopher;

typedef struct s_simulation
{
	long			philosopher_count;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			required_meals;
	pthread_mutex_t	sim_lock;
	pthread_mutex_t	print_lock;
	bool			simulation_ended;
	t_philosopher	*philosophers;
	pthread_mutex_t	*forks;
	long			start_time;
	pthread_t		monitor_thread;
}	t_simulation;

int		init_simulation(int argc, char **argv, t_simulation *sim);
int		create_philosophers(t_simulation *sim);
void	assign_forks(t_philosopher *philo, pthread_mutex_t *forks, long index);
int		init_mutexes(t_simulation *sim);
void	cleanup_simulation(t_simulation *sim);
long	get_current_time_ms(void);
void	precise_sleep(long milliseconds);
long	get_elapsed_time(long start_time);
bool	is_simulation_finished(t_simulation *sim);
int		print_status(t_philosopher *philo, char status);

void	*philosopher_routine(void *arg);
void	philosopher_eat(t_philosopher *philo);
void	philosopher_sleep(t_philosopher *philo);
void	philosopher_think(t_philosopher *philo);
long	get_meals_eaten(t_philosopher *philo);

void	*supervisor_routine(void *arg);
bool	check_philosopher_death(t_philosopher *philo);
bool	are_all_philosophers_satisfied(t_simulation *sim);
void	mark_simulation_end(t_simulation *sim);
int		start_simulation(t_simulation *sim);

int		validate_input(int argc, char **argv, t_simulation *sim);
long	safe_atoi(const char *str);
bool	is_valid_number(const char *str);
int		parse_simulation_args(char **argv, t_simulation *sim);
void	handle_single_philosopher(t_philosopher *philo);

#endif