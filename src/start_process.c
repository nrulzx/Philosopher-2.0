/* ============================= START_PROCESS ============================= */

#include "../inc/philo.h"

int	is_finish(t_thread *thread)
{
	t_data *data;
	int i;
	int finished_eating;

	data = thread->data;
	if (data->must_eat == -1)
		return (0);
	finished_eating = 0;
	i = 0;
	pthread_mutex_lock(&data->meal_mutex);
	while (i < data->philo_num)
	{
		if (data->threads[i].meals_count >= data->must_eat)
			finished_eating++;
		i++;
	}
	pthread_mutex_unlock(&data->meal_mutex);
	if (finished_eating == data->philo_num)
	{
		pthread_mutex_lock(&data->death_mutex);
		data->all_ate = true;
		pthread_mutex_unlock(&data->death_mutex);
		return (1);
	}
	return (0);
}

int	check_died(t_thread *thread, int time_to_die)
{
	long current_time;
	long time_since_last_meal;

	pthread_mutex_lock(&thread->data->meal_mutex);
	current_time = get_time();
	time_since_last_meal = current_time - thread->last_meal;
	pthread_mutex_unlock(&thread->data->meal_mutex);
	if (time_since_last_meal > time_to_die)
	{
		pthread_mutex_lock(&thread->data->death_mutex);
		thread->data->someone_died = true;
		pthread_mutex_unlock(&thread->data->death_mutex);
		print_state(thread->data, thread->id, "died");
		return (1);
	}
	return (0);
}

void	*monitor_process(void *arg)
{
	t_thread	*threads;
	t_data		*data;
	int			i;
	
	threads = (t_thread *)arg;
	data = threads->data;
	
	while (1)
	{
		i = 0;
		while (i < data->philo_num)
		{
			if (check_died(&data->threads[i], data->time_to_die))
				return (NULL);
			if (is_finish(&data->threads[i]))
				return (NULL);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

int	start_process(t_data *data)
{
	int			i;
	pthread_t	monitor;
	
	i = 0;
	while (i < data->philo_num)
	{
		if (pthread_create(&data->threads[i].thread, NULL, 
						thread_action, &data->threads[i]) != 0)
			print_error("Error: Failed to create thread\n");
		i++;
	}
	if (pthread_create(&monitor, NULL, 
					monitor_process, data->threads) != 0)
		print_error("Error: Failed to create monitor thread\n");
	pthread_join(monitor, NULL);
	return (0);
}
