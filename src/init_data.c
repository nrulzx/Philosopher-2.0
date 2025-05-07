#include "../inc/philo.h"

static int	parse_args(t_data *data, int ac, char **av)
{
	if (ac != 5 && ac != 6)
		print_error("Error: Number of argument incorrect");
	if (data->nbr_philo <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_slp <= 0)
		print_error("Error: invalid type of argument");
	if (ac == 6 && data->nbr_meal <= 0)
		return (print_error("Error: Number of meal must be positive"));
	return (0);
}

static	int	init_fork(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philo)
	{
		data->fork[i].id = i + 1;
		if (pthread_mutex_init(&data->fork[i].mutex, NULL) != 0)
			return (free_error(data, "Error: Mutex initialization failed"));
		i++;
	}
	return (0);
}

static int	init_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philo)
	{
		data->thread[i].id = i + 1;
		data->thread[i].count_process = 0;
		data->thread[i].last_process_time = 0;
		data->thread[i].left_fork = data->fork[i];
		data->thread[i].right_fork = &data->fork[(i + 1) % data->nbr_philo];
		data->thread[i].state = THINKING;
		data->thread[i].data = data;
		i++;
	}
	return (0);
}

int	init_data(t_data *data, int ac, char **av)
{
	data->nbr_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_slp = ft_atoi(av[4]);
	data->stop_all = false;
	if (ac == 6)
		data->nbr_meal = ft_atoi(av[5]);
	else
		data->nbr_meal = -1;
	if (parse_args(data, ac, av) != 0)
		return (1);
	data->thread = malloc(sizeof(t_thread) * data->nbr_philo);
	if (!data->thread)
		free_error(data->thread, "Error: Memory allocation failed for thread");
	data->fork = malloc(sizeof(t_fork) * data->nbr_philo);
	if (!data->fork)
		free_error(data->fork, "Error: Memory allocation failed for thread");
	memset(data->thread, 0, sizeof(t_thread) * data->nbr_philo);
	memset(data->fork, 0, sizeof(t_fork) * data->nbr_philo);
	if (init_fork(data) != 0 || init_thread(data) != 0)
		return (1);
	return (0);
}
