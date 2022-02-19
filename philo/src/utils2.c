#include "philo.h"

int	free_all(t_philo *philo, pthread_t *pthread, int return_value)
{
	ft_free((void **)&philo->last_eat, (void **)&philo->fork);
	if (philo->eat_limit)
		ft_free((void **)&philo->eat_times, (void **)&pthread);
	else
		free(pthread);
	return (return_value);
}

void	sleep_and_think(t_philo *philo, int th_index)
{
	put_log(&philo->log, "is sleeping", th_index, "\033[036m");
	action_time(philo->sleep_time);
	put_log(&philo->log, "is thinking", th_index, "\033[033m");
}

void	check_eat_times(t_philo *philo)
{
	int		i;
	bool	eat_enough_times;

	i = 0;
	eat_enough_times = true;
	while (i < philo->th_num || philo->is_end == false)
	{
		if (philo->eat_limit != philo->eat_times[i])
			eat_enough_times = false;
		i++;
	}
	if (eat_enough_times == true)
		philo->is_end = true;
}
