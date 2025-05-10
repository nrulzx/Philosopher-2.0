/* ============================= CLEAN ============================= */

#include "../inc/philo.h"

int	print_error(char *msg)
{
	printf("%s", msg);
	return (1);
}

int	free_error(t_data *data, char *msg)
{
	if (data)
		free(data);
	printf("%s\n", msg);
	return (1);
}

void	print_state(t_data *data, int id, char *state)
{
}

void	cleanup(t_data *data, t_thread *thread)
{
}
