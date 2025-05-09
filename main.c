#include "inc/philo.h"

int	main(int argc, char **argv)
{
	t_data		data;
	t_thread	*thread;

	check_args(ac, av);
	init_data(&data, ac, av);
	start_process(&data, thread);
	cleanup(&data, thread);
	return (0);
}
