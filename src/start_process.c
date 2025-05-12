/* ============================= START_PROCESS ============================= */

#include "../inc/philo.h"

int	check_died(t_thread *thread, int time_to_die)
{
	long	current_time;
	long	time_since_last_meal;

	pthread_mutex_lock(&thread->data->meal_mutex);
	current_time = get_time();
	time_since_last_meal = current_time - thread->last_meal;
	pthread_mutex_unlock(&thread->data->meal_mutex);
	if (time_since_last_meal > time_to_die)
		return (1);
	return (0);
}

int	check_all_ate(t_data *data)
{
	int	i;
	int	finished;

	if (data->must_eat < 0)
		return (0);
	i = 0;
	finished = 0;
	while (i < data->philo_num)
	{
		pthread_mutex_lock(&data->meal_mutex);
		if (data->threads[i].meals_count >= data->must_eat)
			finished++;
		pthread_mutex_unlock(&data->meal_mutex);
		i++;
	}
	return (finished == data->philo_num);
}

static void	monitor_death(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		if (check_died(&data->threads[i], data->time_to_die))
		{
			pthread_mutex_lock(&data->death_mutex);
			data->someone_died = true;
			pthread_mutex_unlock(&data->death_mutex);
			print_state(data, data->threads[i].id, "died");
			break ;
		}
		i++;
	}
}

void	*monitor_process(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		monitor_death(data);
		if (check_all_ate(data))
		{
			pthread_mutex_lock(&data->death_mutex);
			data->all_ate = true;
			pthread_mutex_unlock(&data->death_mutex);
			break ;
		}
		pthread_mutex_lock(&data->death_mutex);
		if (data->someone_died)
		{
			pthread_mutex_unlock(&data->death_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->death_mutex);
		usleep(1000);
	}
	return (NULL);
}

int	start_process(t_data *data)
{
	int			i;
	pthread_t	monitor;

	data->start_time = get_time();
	i = 0;
	while (i < data->philo_num)
	{
		if (pthread_create(&data->threads[i].thread, NULL, thread_action,
				&data->threads[i]) != 0)
			return (1);
		i++;
	}
	if (pthread_create(&monitor, NULL, monitor_process, data) != 0)
		return (1);
	if (pthread_join(monitor, NULL) != 0)
		return (1);
	return (0);
}
