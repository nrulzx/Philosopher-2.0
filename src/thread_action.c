/* ============================= THREAD_ACTION ============================= */

#include "../inc/philo.h"

static int	philo_eat(t_thread *thread)
{
	t_data	*data;
	int		right_fork;
	int 	left_fork;

	data = thread->data;
	right_fork = thread->right_fork;
	left_fork = thread->left_fork;
	pthread_mutex_lock(&data->forks[right_fork].mutex);
	print_state(data, thread->id, "has taken a fork");
	if (data->philo_num == 1)
	{
		ft_sleep(data->time_to_die + 10);
		pthread_mutex_unlock(&data->forks[right_fork].mutex);
		return (1);
	}
	pthread_mutex_lock(&data->forks[left_fork].mutex);
	print_state(data, thread->id, "has taken a fork");
	print_state(data, thread->id, "is eating");
	thread->state = EATING;
	pthread_mutex_lock(&data->meal_mutex);
	thread->last_meal = get_time();
	thread->meals_count++;
	pthread_mutex_unlock(&data->meal_mutex);
	ft_sleep(data->time_to_eat);
	pthread_mutex_unlock(&data->forks[right_fork].mutex);
	pthread_mutex_unlock(&data->forks[left_fork].mutex);
	return (0);
}

static int	philo_sleep(t_thread *thread)
{
	t_data *data;

	data = thread->data;
	print_state(data, thread->id, "is sleeping");
	thread->state = SLEEPING;
	ft_sleep(data->time_to_sleep);
	return (0);
}

static int	philo_think(t_thread *thread)
{
    print_state(thread->data, thread->id, "is thinking");
	thread->state = THINKING;
	usleep(500);
	return (0);
}

void	*thread_action(void *arg)
{
	t_thread	*thread;
	t_data		*data;
	
	thread = (t_thread *)arg;
	data = thread->data;
	if (thread->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		pthread_mutex_lock(&data->death_mutex);
		if (data->someone_died || data->all_ate)
		{
			pthread_mutex_unlock(&data->death_mutex);
			break;
		}
		pthread_mutex_unlock(&data->death_mutex);
		if (philo_eat(thread))
			break;
		if (philo_sleep(thread))
			break;
		if (philo_think(thread))
			break;
	}	
	return (NULL);
}
