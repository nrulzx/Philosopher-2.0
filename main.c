#include "inc/philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (check_args(ac, av))
		return (1);
	init_data(&data, ac, av);
	if (!data.forks || !data.threads)
	{
		cleanup(&data, NULL);
		return (print_error("Error: Initialization failed\n"));
	}
	start_process(&data);
	cleanup(&data, data.threads);
	return (0);
}
