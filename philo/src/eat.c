#include "philo.h"

int	eating(t_philo *philo, size_t pthread_index)
{
	size_t	left_index;

	left_index = get_left_index(philo->pthread_num, pthread_index);
	philo->last_eat[pthread_index] = get_current_time();
	put_log(&philo->log, "is eating", pthread_index);
	action_time(philo->eat_time);
	if (pthread_mutex_unlock(&philo->fork[pthread_index]) != 0)
		return (ERROR);
	if (pthread_mutex_unlock(&philo->fork[left_index]) != 0)
		return (ERROR);
	return (0);
}

void	init_last_eat(size_t *last_eat, size_t pthread_num)
{
	size_t	i;
	size_t	current_time;

	i = 0;
	current_time = get_current_time();
	while (i < pthread_num)
		last_eat[i++] = current_time;
}
