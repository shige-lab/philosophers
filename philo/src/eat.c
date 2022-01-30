#include "philo.h"

int	eating(t_philo *philo, size_t pthread_index)
{
	size_t	left_index;

	left_index = get_left_index(philo->pthread_num, pthread_index);
	put_log(&philo->log, "is eating", pthread_index + 1);
	usleep(philo->eat_time);
	if (pthread_mutex_unlock(&philo->fork[pthread_index]) != 0)
		return (ERROR);
	if (pthread_mutex_unlock(&philo->fork[left_index]) != 0)
		return (ERROR);
}
