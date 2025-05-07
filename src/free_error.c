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
