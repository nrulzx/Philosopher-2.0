#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef enum e_state
{
	THINKING,
	EATING,
	SLEEPING,
	DIED
}					t_state;

typedef struct s_thread
{
	int				id;
	int				process;
	int				left_fork;
	int				right_fork;
	long			last_process;
	pthread_mutex_t	mutex_process;
	t_state			state;
	struct s_data	*data;
}					t_thread;

typedef struct s_data
{
	int				nbr_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_slp;
	int				must_eat;
	int				dead;
	int				finish;
	long			start_time;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	fork[200];
	t_thread		*threads;
}					t_data;

/* ========================== clean ========================== */
int					print_error(char *msg);
int					free_error(t_data *data, char *msg);
void				print_state(t_data *data, int id, char *state);
void				print_death_message(t_data *data, int id);
void				cleanup(t_data *data, t_thread *thread);

/* ========================= init_data ======================== */
int					check_args(t_data *data, int ac, char **av);
void				init_data(t_data *data, int ac, char **av);
void				init_forks(t_data *data);
t_thread			*init_philosophers(t_data *data);

/* ========================== start_process ========================== */
void				*monitor_routine(void *arg);
int					start_process(t_data *data, t_thread *philos);

/* ========================== thread_action ========================== */
void				*thread_action(void *arg);

/* ========================== utils ========================== */
int					ft_atoi(const char *str);
int					is_number(char *str);
long				get_time(void);
void				ft_sleep(long time);

#endif
