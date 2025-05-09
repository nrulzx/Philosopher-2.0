/* ============================= INIT_DATA ============================= */

#include "../inc/philo.h"

static void	check_args(t_data *data, int ac, char **av)
{
	int	i;

	if (ac != 5 && ac != 6)
		print_error("Error: Number of argument incorrect");
	while (i < ac)
	{
		if (!is_number(argv[i]) || ft_atoi(argv[i]) <= 0)
			print_error("Error: invalid type of argument");
		i++;
	}
	if (ac == 6 && data->must_eat <= 0)
		return (print_error("Error: must_eat need to be positive"));
}

static void	init_args(t_data *data, int ac, char **av)
{
	data->nb_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->nbr_eat = -1;
	if (ac == 6)
		data->nbr_eat = ft_atoi(argv[5]);
	data->dead = 0;
	data->finish = 0;
	pthread_mutex_init(&data->write_mutex, NULL);
	pthread_mutex_init(&data->dead_mutex, NULL);
}

static void	init_thrad(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philo)
	{
		pthread_mutex_init(&data->fork[i].id, NULL);
		data->thread[i].id = i + 1;
		data->thread[i].count_process = 0;
		data->thread[i].last_process_time = 0;
		data->thread[i].left_fork = &data->fork[i];
		data->thread[i].right_fork = &data->fork[(i + 1) % data->nbr_philo];
		data->thread[i].state = THINKING;
		data->thread[i].data = data;
		i++;
	}
}

void	init_data(t_data *data, int ac, char **av)
{
	check_args(data, ac, av);
	inti_args(data *data, ac, av);
	init_thread(data);
}
	
