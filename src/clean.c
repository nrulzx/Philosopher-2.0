/* ============================= CLEAN ============================= */

#include "../inc/philo.h"

int	print_error(char *msg)
{
	printf("%s", msg);
	return (1);
}

int	free_error(t_data *data, char *msg)
{
	free(data);
	printf("%s\n", msg);
	return (1);
}

void	print_state(t_data *data, int id, char *state)
{
	long	time;

	pthread_mutex_lock(&data->write_mutex);
	time = get_time() - data->start_time;
	if (!data->dead)
		printf("%ld %d %s\n", time, id, state);
	pthread_mutex_unlock(&data->write_mutex);
}

void	print_death_message(t_data *data, int id)
{
	pthread_mutex_lock(&data->write_mutex);
	if (!data->dead)
	{
		printf("%ld %d died\n", get_time() - data->start_time, id);
		data->dead = 1;
	}
	pthread_mutex_unlock(&data->write_mutex);
}

void	cleanup(t_data *data, t_thread *thread)
{
	int	i;

	(void)thread;
	i = 0;
	while (i < data->nbr_philo)
	{
		pthread_mutex_destroy(&data->fork[i]);
		pthread_mutex_destroy(&data->threads[i].mutex_process);
		i++;
	}
	pthread_mutex_destroy(&data->write_mutex);
	pthread_mutex_destroy(&data->dead_mutex);
	free(data->threads);
}
