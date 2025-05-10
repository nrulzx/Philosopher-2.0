/* ============================= START_PROCESS ============================= */

#include "../inc/philo.h"

static int	check_if_died(t_thread *thread, int time_to_die)
{
	long	current_time;

	current_time = get_time();
	pthread_mutex_lock(&thread->mutex_process);
	if (current_time - thread->last_process > time_to_die)
	{
		thread->state = DIED;
		pthread_mutex_unlock(&thread->mutex_process);
		return (1);
	}
	pthread_mutex_unlock(&thread->mutex_process);
	return (0);
}

static int	check_nbr_meal(t_data *data)
{
	int	i;
	int	count;

	if (data->must_eat < 0)
		return (0);
	i = 0;
	count = 0;
	while (i < data->nbr_philo)
	{
		if (data->threads[i].process >= data->must_eat)
			count++;
		i++;
	}
	return (count == data->nbr_philo);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (!data->dead && !data->finish)
	{
		i = 0;
		while (i < data->nbr_philo && !data->dead)
		{
			if (check_if_died(&data->threads[i++], data->time_to_die))
			{
				print_death_message(data, data->threads[i - 1].id);
				break ;
			}
		}
		if (data->dead || check_nbr_meal(data))
		{
			pthread_mutex_lock(&data->dead_mutex);
			data->finish = 1;
			pthread_mutex_unlock(&data->dead_mutex);
			break ;
		}
		usleep(1000);
	}
	return (NULL);
}

int	start_process(t_data *data, t_thread *philos)
{
	int			i;
	pthread_t	threads_id[200];
	pthread_t	monitor;

	(void)philos;
	if (!init_philosophers(data))
		return (1);
	i = 0;
	while (i < data->nbr_philo)
	{
		if (pthread_create(&threads_id[i], NULL, thread_action,
				&data->threads[i]))
			return (1);
		i++;
	}
	if (pthread_create(&monitor, NULL, monitor_routine, data))
		return (1);
	i = 0;
	while (i < data->nbr_philo)
	{
		pthread_join(threads_id[i], NULL);
		i++;
	}
	pthread_join(monitor, NULL);
	return (0);
}
