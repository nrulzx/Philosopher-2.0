#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>

typedef enum e_state
{
	THINKING,
	EATING,
	SLEEPING,
	DIED
}	t_state;

typedef struct s_forks
{
	pthread_mutex_t	mutex;
	int				id;
}					t_forks;

typedef struct s_thread
{
	
}					t_thread;

typedef struct s_data
{
	
}					t_data;

/* ========================== clean ========================== */
int					print_error(char *msg);
int					free_error(t_data *data, char *msg);
void				print_state(t_data *data, int id, char *state);
void				cleanup(t_data *data, t_thread *thread);

/* ========================= init_data ======================== */
int					check_args(t_data *data, int ac, char **av);
int					init_args(t_data *data, int ac, char **av);
t_data				init_data(t_data *data, int ac, char **av);
t_forks				init_forks(t_data *data);
t_thread			*init_thread(t_data *data);

/* ========================== start_process ========================== */
int					is_finish(t_thread *thread);
int					check_died(t_thread *thread, int time_to_die);
int					monitor_process(void *arg);
int					start_process(t_data *data, t_thread *philos);

/* ========================== thread_action ========================== */
int					thread_action(void *arg);

/* ========================== utils ========================== */
int					ft_atoi(const char *str);
int					is_number(char *str);
long				get_time(void);
void				ft_sleep(long time);

#endif
