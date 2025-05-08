/* ============================= THREAD_PROCESS ============================= */

#include "../inc/philo.h"

static void	thread_eat(t_thread *thread)
{
	pthread_mutex_lock(&thread->left_fork->mutex);
	pthread_mutex_lock(&thread->right_fork->mutex);
	thread->state = EATING;
	thread->last_process_time = get_time();
	usleep(thread->data->time_to_eat * 1000);
	thread->count_process++;
	pthread_mutex_unlock(&thread->right_fork->mutex);
	pthread_mutex_unlock(&thread->left_fork->mutex);
}

static void	thread_sleep(t_thread *thread)
{
	thread->state = SLEEPING;
	usleep(thread->data->time_to_slp * 1000);
}

static void	thread_think(t_thread *thread)
{
	thread->state = THINKING;
	usleep(thread->data->time_to_die * 1000);
}

void	*thread_process(void *arg)
{
	t_thread *thread;
	t_data *data;

	thread = (t_thread *)arg;
	data = thread->data;
	while (!data->stop_all)
	{
		if (thread->state == THINKING)
			thread_eat(thread);
		else if (thread->state == EATING)
			thread_sleep(thread);
		else if (thread->state == SLEEPING)
			thread_think(thread);
	}
	return (NULL);
}