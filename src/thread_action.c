/* ============================= THREAD_ACTION ============================= */

#include "../inc/philo.h"

static int	is_finish(t_thread *thread)
{
	pthread_mutex_lock(&thread->data->dead_mutex);
	if (thread->data->dead)
	{
		pthread_mutex_unlock(&thread->data->dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(&thread->data->dead_mutex);
	return (0);
}	

int	philo_eat(t_thread *thread)
{
	if (is_finish(thread))
		return (1);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->data->fork[philo->right_fork_id]);
		print_status(philo->data, philo->id, "has taken a fork");
		pthread_mutex_lock(&philo->data->fork[philo->left_fork_id]);
		print_status(philo->data, philo->id, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->data->fork[philo->left_fork_id]);
		print_status(philo->data, philo->id, "has taken a fork");
		pthread_mutex_lock(&philo->data->fork[philo->right_fork_id]);
		print_status(philo->data, philo->id, "has taken a fork");
	}
	print_status(philo->data, philo->id, "is eating");
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->meal_mutex);
	ft_sleep(philo->data->time_to_eat);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->fork[philo->left_fork_id]);
	pthread_mutex_unlock(&philo->data->fork[philo->right_fork_id]);
	return (0);
}

void	philo_sleep(t_philo *philo)
{
	if (is_simulation_over(philo))
		return;
	print_status(philo->data, philo->id, "is sleeping");
	ft_sleep(philo->data->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	if (is_simulation_over(philo))
		return;
	print_status(philo->data, philo->id, "is thinking");
	if (philo->data->nb_philos % 2 != 0)
		usleep(500);
}

void	*thread_action(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!is_simulation_over(philo))
	{
		if (philo_eat(philo))
			break;
		if (philo->data->must_eat != -1 && 
			philo->meals_eaten >= philo->data->must_eat)
			break;
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}
