#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
# include <string.h>

typedef enum e_state
{
	THINKING,
	EATING,
	SLEEPING,
	DIED
}	t_state;

typedef struct s_fork
{
	int				id;
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_thread
{
	struct s_data	*data;
	int				id;
	int				count_process;
	long			last_process_time;
	pthread_t		thread;
	t_state			state;
	t_fork			*left_fork;
	t_fork			*right_fork;
}	t_thread;

typedef struct s_data
{
	int				nbr_philo;	
	int				time_to_die;	
	int				time_to_eat;	
	int				time_to_slp;
	int				nbr_meal;
	bool			stop_all;
	t_fork			*fork;
	t_thread		*thread;
}	t_data;

/* ____________________ init_data ___________________ */
int		init_data(t_data *data, int ac, char **av);

/* ____________________ free_error ___________________ */
int		print_error(char *msg);
int		free_error(t_data *data, char *msg);
void	cleanup(t_data *data);

/* ____________________ libft_utils ___________________ */
int		ft_atoi(const char *str);

/* ____________________ thread_process ___________________ */
void    *thread_process(void *arg)

#endif