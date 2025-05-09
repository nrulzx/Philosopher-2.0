/* ============================= START_PROCESS ============================= */

#include "../inc/philo.h"

static int	check_if_died(t_thread *thread, int time_to_die)
{
    long    current_time;

    current_time = get_time();
    if (current_time - thread->last_process_time > time_to_die)
    {
        thread->state = DIED;
        return (1);
    }
    return (0);
}

static void print_death_message(t_thread *thread)
{
    printf("%ld %d died\n", get_time(), thread->id);
}

static int	check_nbr_meal(t_data *data)
{
    int	i;
    int	nbr;

    if (data->nbr_meal < 0)
        return (0);
    i = 0;
    nbr = 0;
    while (i < data->nbr_philo)
    {
        if (data->thread[i].count_process >= data->nbr_meal)
            nbr++;
        i++;
    }
    return (nbr == data->nbr_philo);
}

void    *monitor_process(void *arg)
{
    t_data  *data;
    int     i;

    data = (t_data *)arg;
    while (!data->stop_all)
    {
        i = 0;
        while (i < data->nbr_philo)
        {
            if (check_if_died(&data->thread[i], data->time_to_die))
            {
                print_death_message(&data->thread[i]);
                data->stop_all = true;
                break;
            }
            i++;
        }
        if (data->stop_all || check_nbr_meal(data))
        {
            data->stop_all = true;
            break;
        }
        usleep(100);
    }
    return (NULL);
}

int	start_process(t_data *data, t_philo *philos)
{
	int			i;
	pthread_t	monitor[200];

	data->start_time = get_time();
	i = 0;
	while (i < data->nbr_philo)
	{
		philo[i].last_process = data->start_time;
		if (pthread_create(&data->thread[i], NULL, thread_action, &philo[i]))
			return (1);
		if (pthread_create(&monitor[i], NULL, monitor_process, &philo[i]))
			return (1);
	}
	i = 0;
	while (i < data->nb_philos)
	{
		pthread_join(data->thread[i], NULL);
		pthread_join(monitor[i], NULL);
	}
	return (0);
}
