#include "../inc/philo.h"

static int	create_threads(t_data *data)
{
	int i;

	i = 0;
	while (i < data->nbr_philo)
	{
		if (pthread_create(&data->thread[i].thread, NULL, thread_process,
				&data->thread[i]) != 0)
			return (free_error(data, "Error: Thread creation failed"));
		i++;
	}
	return (0);
}
