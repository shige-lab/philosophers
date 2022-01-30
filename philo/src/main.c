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
	philo->die_time =	600;
	philo->eat_time = 300000;
	philo->sleep_time = 400000;
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
	if (pthread_mutex_init(&philo->act, NULL) != 0)
		return (ERROR);
	if (pthread_mutex_init(&philo->log, NULL) != 0)
		return (ERROR);
	return (0);
}

bool	can_get_forks(t_philo *philo, size_t pthread_index)
{
	size_t	left_index;

	left_index = get_left_index(philo->pthread_num, pthread_index);
	if (pthread_mutex_lock(&philo->fork[left_index]) == 0)
	{
		put_log(&philo->log, "has token a fork", pthread_index + 1);
		if (pthread_mutex_lock(&philo->fork[pthread_index]) != 0)
		{
			pthread_mutex_unlock(&philo->fork[left_index]);
			return (false);
		}
	}
	put_log(&philo->log, "has token a fork", pthread_index + 1);
	return (true);
}

void	start_philo_life(void *p)
{
	t_philo	*philo;
	size_t	pthread_index;

	philo = p;
	pthread_index = philo->num_x;
	while (true)
	{
		if (pthread_mutex_lock(&philo->act) == 0)
		{
			if (can_get_forks(philo, pthread_index) == true)
			{
				pthread_mutex_unlock(&philo->act);
				eating(philo, pthread_index);
				put_log(&philo->log, "is sleeping", pthread_index + 1);
				usleep(philo->sleep_time);
				put_log(&philo->log, "is thinking", pthread_index + 1);
			}
			else
				pthread_mutex_unlock(&philo->act);
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
	while (i < philo.pthread_num)
	{
		philo.num_x = i;
		if (pthread_create(&pthread[0], NULL, start_philo_life, &philo) != 0)
			return (0);
		usleep(300);
		i++;
	}
	while (true)
	{
		if (philo.is_dead == true)
		break ;
	}
	system("leaks philo");
	return (0);
}
