/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshigena <tshigena@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 21:57:36 by tshigena          #+#    #+#             */
/*   Updated: 2022/01/04 22:32:32 by tshigena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_info_from_argv(t_philo *philo, char **argv)
{
	philo->pthread_num = atoi(argv[1]);
	philo->die_time =	800;
	philo->eat_time = 500;
	philo->sleep_time = 350;
	return (0);
}

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

bool	can_get_forks(t_philo *philo, size_t pthread_index)
{
	size_t	left_index;
	bool	flag;
	left_index = get_left_index(philo->pthread_num, pthread_index);
	if (pthread_mutex_lock(&philo->fork[left_index]) == 0)
	{
		put_log(&philo->log, "has taken a fork", pthread_index);
		if (pthread_mutex_lock(&philo->fork[pthread_index]) != 0)
		{
			pthread_mutex_unlock(&philo->fork[left_index]);
			flag = false;
		}
		else
		{
			put_log(&philo->log, "has taken a fork", pthread_index);
			flag = true;
		}
	}
	return (flag);
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

void	set_num_x(t_philo *philo)
{
	while (true)
	{
		if (pthread_mutex_lock(&philo->_num_x) == 0)
		{
			return ;
		}
	}
}

int	main(int argc, char **argv)
{
	pthread_t	*pthread;
	t_philo		philo;
	size_t		i;

	if (get_info_from_argv(&philo, argv) == ERROR)
		return (1);
	pthread = (pthread_t *)calloc(philo.pthread_num, sizeof(pthread_t));
	if (pthread == NULL)
		return (1);
	if (init_t_philo(&philo) == ERROR)
		return (1);
	i = 0;
	philo.num_x = 0;
	while (i < philo.pthread_num)
	{
		if (pthread_create(&pthread[i], NULL, start_philo_life, &philo) != 0)
			return (0);
		usleep(100);
		pthread_detach(pthread[i]);
		i++;
	}
	while (true)
	{
		if (philo.is_dead == true)
		break ;
	}
//	system("leaks philo");
	return (0);
}
