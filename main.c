#include "inc/philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	if (init_data(&data, ac, av) != 0)
		return (1);
	monitor_philosophers(&data);
	join_threads(&data);
	cleanup_resources(&data);
	return (0);
}
