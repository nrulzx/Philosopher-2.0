/* ============================= THREAD_ACTION ============================= */

#include "../inc/philo.h"

static int	is_finish(t_thread *thread)
{
	pthread_mutex_lock(&thread->data->dead_mutex);
	if (thread->data->dead || thread->data->finish)
	{
		pthread_mutex_unlock(&thread->data->dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(&thread->data->dead_mutex);
	return (0);
}

static int	philo_eat(t_thread *thread)
{
	if (is_finish(thread))
		return (1);
	
	pthread_mutex_lock(&thread->data->fork[thread->left_fork]);
	print_state(thread->data, thread->id, "has taken a fork");
	if (thread->data->nbr_philo == 1)
	{
		ft_sleep(thread->data->time_to_die);
		pthread_mutex_unlock(&thread->data->fork[thread->left_fork]);
		return (1);
	}
	pthread_mutex_lock(&thread->data->fork[thread->right_fork]);
	print_state(thread->data, thread->id, "has taken a fork");
	
	print_state(thread->data, thread->id, "is eating");
	pthread_mutex_lock(&thread->mutex_process);
	thread->last_process = get_time();
	pthread_mutex_unlock(&thread->mutex_process);
	ft_sleep(thread->data->time_to_eat);
	thread->process++;
	
	pthread_mutex_unlock(&thread->data->fork[thread->left_fork]);
	pthread_mutex_unlock(&thread->data->fork[thread->right_fork]);
	return (0);
}

static void	philo_sleep(t_thread *thread)
{
	if (is_finish(thread))
		return;
	print_state(thread->data, thread->id, "is sleeping");
	ft_sleep(thread->data->time_to_slp);
}

static void	philo_think(t_thread *thread)
{
	if (is_finish(thread))
		return;
	print_state(thread->data, thread->id, "is thinking");
}

void	*thread_action(void *arg)
{
	t_thread	*thread;

	thread = (t_thread *)arg;
	if (thread->id % 2 == 0)
		usleep(1000);
	
	while (!is_finish(thread))
	{
		if (philo_eat(thread))
			break;
		if (thread->data->must_eat != -1 && 
			thread->process >= thread->data->must_eat)
			break;
		philo_sleep(thread);
		philo_think(thread);
	}
	return (NULL);
} 