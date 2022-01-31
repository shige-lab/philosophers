#include "philo.h"

int	init_t_philo(t_philo *philo)
{
	size_t	i;

	i = 0;
	philo->is_dead = false;
	philo->fork = (pthread_mutex_t *)calloc(philo->pthread_num, sizeof(pthread_mutex_t));
	philo->last_eat = (size_t *)calloc(philo->pthread_num, sizeof(size_t));
	if (philo->fork == NULL || philo->last_eat == NULL)
	{
		ft_free((void **)&philo->fork ,(void **)&philo->last_eat);
		return (ERROR);
	}
	while (i < philo->pthread_num)
	{
		if (pthread_mutex_init(&philo->fork[i++], NULL) != 0)
			return (ERROR);
	}
	if (pthread_mutex_init(&philo->log, NULL) != 0)
		return (ERROR);
	init_last_eat(philo, philo->pthread_num);
	pthread_mutex_init(&philo->_num_x, NULL);
	return (0);
}

void	*start_philo_life(void *p)
{
	t_philo	*philo;
	size_t	pthread_index;

	philo = p;
	set_num_x(philo);
	pthread_index = philo->num_x;
	philo->num_x++;
	pthread_mutex_unlock(&philo->_num_x);
	while (true)
	{
		if (get_current_time() - philo->last_eat[pthread_index] > philo->die_time)
		{
			put_log(&philo->log, "died", pthread_index);
			philo->is_dead = true;
			return (NULL);
		}
		if (can_get_forks(philo, pthread_index) == true)
		{
			eating(philo, pthread_index);
			put_log(&philo->log, "is sleeping", pthread_index);
			action_time(philo->sleep_time);
			put_log(&philo->log, "is thinking", pthread_index);
		}
	}
	return (NULL);
}
