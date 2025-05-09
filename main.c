#include "inc/philo.h"

int	main(int argc, char **argv)
{
	t_data		data;

	if (check_args(&data, argc, argv))
		return (1);
	init_data(&data, argc, argv);
	start_process(&data, NULL);
	cleanup(&data, NULL);
	return (0);
}
