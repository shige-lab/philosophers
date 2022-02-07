#include "philo.h"

int	init_t_philo(t_philo *philo)
{
	int	i;

	i = 0;
	philo->is_dead = false;
	philo->fork = (pthread_mutex_t *)ft_calloc
		(philo->th_num + 1, sizeof(pthread_mutex_t));
	philo->last_eat = (size_t *)ft_calloc
		((size_t)philo->th_num + 1, sizeof(size_t));
	if (philo->fork == NULL || philo->last_eat == NULL)
		return (ERROR);
	while (i < philo->th_num)
	{
		if (pthread_mutex_init(&philo->fork[i++], NULL) != 0)
			return (ERROR);
	}
	if (pthread_mutex_init(&philo->log, NULL) != 0)
		return (ERROR);
	init_last_eat(philo, philo->th_num);
	pthread_mutex_init(&philo->_num_x, NULL);
	return (0);
}

void	*start_philo_life(void *p)
{
	int		th_index;
	t_philo	*philo;

	philo = p;
	set_num_x(philo, &th_index);
	while (philo->is_dead == false)
	{
		if (get_current_time() - philo->last_eat[th_index] > (size_t)philo->die_time)
		{
			put_log(&philo->log, "died", th_index, "\033[035m");
			philo->is_dead = true;
			return (NULL);
		}
		if (can_get_forks(philo, th_index) == true)
		{
			eating(philo, th_index);
			if (philo->is_dead == true)
				return (NULL);
			put_log(&philo->log, "is sleeping", th_index, "\033[036m");
			action_time(philo->sleep_time);
			put_log(&philo->log, "is thinking", th_index, "\033[033m");
		}
	}
	return (NULL);
}
