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

void	cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philo)
	{
		pthread_mutex_destroy(&data->fork[i].mutex);
		i++;
	}
	if (data->thread)
		free(data->thread);
	if (data->fork)
		free(data->fork);
}
