#include "philo.h"

void	free_all(t_philo *philo, pthread_t *pthread)
{
	ft_free((void **)&philo->last_eat, (void **)&philo->fork);
	if (philo->eat_limit)
		ft_free((void **)&philo->eat_times, (void **)&pthread);
	else
		free(pthread);
}
