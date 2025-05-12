/* ============================= THREAD_ACTION ============================= */

#include "../inc/philo.h"

static int	philo_eat(t_thread *thread)
{
	t_data	*data;
	int		right_fork;
	int		left_fork;

	data = thread->data;
	right_fork = thread->right_fork;
	left_fork = thread->left_fork;
	pthread_mutex_lock(&data->forks[right_fork].mutex);
	print_state(data, thread->id, "has taken a fork");
	if (data->philo_num == 1)
		return (handle_single_philo(data, right_fork));
	pthread_mutex_lock(&data->forks[left_fork].mutex);
	print_state(data, thread->id, "has taken a fork");
	print_state(data, thread->id, "is eating");
	thread->state = EATING;
	update_meal_time(thread);
	ft_sleep(data->time_to_eat);
	release_forks(data, right_fork, left_fork);
	return (0);
}

int	philo_action(t_thread *thread, t_state state)
{
	t_data	*data;

	data = thread->data;
	if (state == SLEEPING)
	{
		print_state(data, thread->id, "is sleeping");
		thread->state = SLEEPING;
		ft_sleep(data->time_to_sleep);
	}
	else if (state == THINKING)
	{
		print_state(data, thread->id, "is thinking");
		thread->state = THINKING;
		usleep(500);
	}
	return (0);
}

void	*thread_action(void *arg)
{
	t_thread	*thread;
	t_data		*data;

	thread = (t_thread *)arg;
	data = thread->data;
	if (thread->id % 2 == 0)
		usleep(thread->data->time_to_eat * 100);
	while (1)
	{
		pthread_mutex_lock(&data->death_mutex);
		if (data->someone_died || data->all_ate)
		{
			pthread_mutex_unlock(&data->death_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->death_mutex);
		if (philo_eat(thread))
			break ;
		if (philo_action(thread, SLEEPING))
			break ;
		if (philo_action(thread, THINKING))
			break ;
	}
	return (NULL);
}
