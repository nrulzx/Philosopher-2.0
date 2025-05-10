/* ============================= INIT_DATA ============================= */

#include "../inc/philo.h"

int	check_args(t_data *data, int ac, char **av)
{
	int	i;

	(void)data;
	i = 1;
	if (ac != 5 && ac != 6)
		return (print_error("Error: Number of argument incorrect\n"));
	while (i < ac)
	{
		if (!is_number(av[i]) || ft_atoi(av[i]) <= 0)
			return (print_error("Error: invalid type of argument\n"));
		i++;
	}
	if (ac == 6 && ft_atoi(av[5]) <= 0)
		return (print_error("Error: must_eat need to be positive\n"));
	return (0);
}

static void	init_args(t_data *data, int ac, char **av)
{
	data->nbr_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_slp = ft_atoi(av[4]);
	data->must_eat = -1;
	if (ac == 6)
		data->must_eat = ft_atoi(av[5]);
	data->dead = 0;
	data->finish = 0;
	data->start_time = get_time();
	pthread_mutex_init(&data->write_mutex, NULL);
	pthread_mutex_init(&data->dead_mutex, NULL);
}

void	init_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philo)
	{
		pthread_mutex_init(&data->fork[i], NULL);
		i++;
	}
}

t_thread	*init_philosophers(t_data *data)
{
	int	i;

	data->threads = malloc(sizeof(t_thread) * data->nbr_philo);
	if (!data->threads)
		return (NULL);
	i = 0;
	while (i < data->nbr_philo)
	{
		data->threads[i].id = i + 1;
		data->threads[i].process = 0;
		data->threads[i].left_fork = i;
		data->threads[i].right_fork = (i + 1) % data->nbr_philo;
		data->threads[i].last_process = get_time();
		pthread_mutex_init(&data->threads[i].mutex_process, NULL);
		data->threads[i].state = THINKING;
		data->threads[i].data = data;
		i++;
	}
	return (data->threads);
}

void	init_data(t_data *data, int ac, char **av)
{
	init_args(data, ac, av);
	init_forks(data);
	data->threads = NULL;
}
