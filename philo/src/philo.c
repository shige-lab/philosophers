#include "philo.h"

int	init_t_philo(t_philo *philo)
{
	size_t	i;

	i = 0;
	philo->is_dead = false;
	philo->fork = (pthread_mutex_t *)ft_calloc
		(philo->th_num, sizeof(pthread_mutex_t));
	philo->last_eat = (size_t *)ft_calloc(philo->th_num, sizeof(size_t));
	if (philo->fork == NULL || philo->last_eat == NULL)
	{
		ft_free((void **)&philo->fork, (void **)&philo->last_eat);
		return (ERROR);
	}
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
	t_philo	*philo;
	size_t	th_index;

	philo = p;
	set_num_x(philo);
	th_index = philo->num_x;
	philo->num_x++;
	pthread_mutex_unlock(&philo->_num_x);
	while (true)
	{
		if (get_current_time() - philo->last_eat[th_index] > philo->die_time)
		{
			put_log(&philo->log, "died", th_index);
			philo->is_dead = true;
			return (NULL);
		}
		if (can_get_forks(philo, th_index) == true)
		{
			eating(philo, th_index);
			put_log(&philo->log, "is sleeping", th_index);
			action_time(philo->sleep_time);
			put_log(&philo->log, "is thinking", th_index);
		}
	}
	return (NULL);
}
