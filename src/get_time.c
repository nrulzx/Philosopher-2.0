#include "../inc/philo.h"

int	get_time(void)
{
	struct timeval  tv;
	int             time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}
