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
