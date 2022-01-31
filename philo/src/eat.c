#include "philo.h"

int	eating(t_philo *philo, size_t th_index)
{
	size_t	left_index;

	left_index = get_left_index(philo->th_num, th_index);
	put_log(&philo->log, "is eating", th_index);
	philo->last_eat[th_index] = get_current_time();
	action_time(philo->eat_time);
	if (pthread_mutex_unlock(&philo->fork[th_index]) != 0)
		return (ERROR);
	if (pthread_mutex_unlock(&philo->fork[left_index]) != 0)
		return (ERROR);
	return (0);
}

void	init_last_eat(t_philo *philo, size_t th_num)
{
	size_t	i;
	size_t	current_time;

	i = 0;
	current_time = get_current_time();
	while (i < th_num)
		philo->last_eat[i++] = current_time;
}
