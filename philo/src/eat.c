#include "philo.h"

void	eating(t_philo *philo, size_t th_index)
{
	size_t	left_index;

	left_index = get_left_index(philo->th_num, th_index);
	put_log(&philo->log, "is eating", th_index, "\033[031m");
	philo->last_eat[th_index] = get_current_time();
	action_time(philo->eat_time);
	pthread_mutex_unlock(&philo->fork[left_index]);
	pthread_mutex_unlock(&philo->fork[th_index]);
	if (philo->eat_limit)
		philo->eat_times[th_index] += 1;
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
