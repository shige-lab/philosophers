/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshigena <tshigena@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 21:57:36 by tshigena          #+#    #+#             */
/*   Updated: 2022/03/02 01:28:28 by tshigena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_info_from_argv(t_philo *philo, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (ERROR);
	if (is_str_unsigned_num_by_atoi(&philo->th_num, argv[1]) == false
		|| philo->th_num == 0
		|| is_str_unsigned_num_by_atoi(&philo->die_time, argv[2]) == false
		|| is_str_unsigned_num_by_atoi(&philo->eat_time, argv[3]) == false
		|| is_str_unsigned_num_by_atoi(&philo->sleep_time, argv[4]) == false)
		return (ERROR);
	if (argv[5])
	{
		if (is_str_unsigned_num_by_atoi(&philo->eat_limit, argv[5]) == false
			|| philo->eat_limit == 0)
			return (ERROR);
		philo->eat_times = (int *)ft_calloc
			((size_t)philo->th_num + 1, sizeof(int));
		if (philo->eat_times == NULL)
			return (ERROR);
	}
	else
		philo->eat_limit = 0;
	return (0);
}

bool	can_get_forks(t_philo *philo, size_t th_index)
{
	size_t	left_index;

	left_index = get_left_index(philo->th_num, th_index);
	if (pthread_mutex_lock(&philo->fork[left_index]) == 0)
	{
		put_log(&philo->log, "has taken a fork", th_index);
		if (pthread_mutex_lock(&philo->fork[th_index]) != 0)
		{
			pthread_mutex_unlock(&philo->fork[left_index]);
			return (false);
		}
		else
			put_log(&philo->log, "has taken a fork", th_index);
	}
	if (get_current_time() - philo->last_eat[th_index]
		> (size_t)philo->die_time)
	{
		put_log(&philo->log, "died", th_index);
		philo->is_end = true;
	}
	return (true);
}

void	wait_until_someone_died(t_philo *philo)
{
	while (true)
	{
		if (philo->eat_limit > 0)
			check_eat_times(philo);
		if (philo->is_end == true)
			break ;
	}
	if (philo->eat_time > philo->sleep_time)
		usleep(philo->eat_time);
	else
		usleep(philo->sleep_time);
}

int	main(int argc, char **argv)
{
	pthread_t	*pthread;
	t_philo		philo;
	int			i;

	if (get_info_from_argv(&philo, argc, argv) == ERROR)
		return (1);
	pthread = (pthread_t *)ft_calloc(philo.th_num, sizeof(pthread_t));
	if (init_t_philo(&philo) == ERROR || pthread == NULL)
		return (free_all(&philo, pthread, 1));
	i = 0;
	philo.num_x = 0;
	if (philo.th_num == 1)
		return (philo_one_life(&philo, pthread));
	while (i < philo.th_num)
	{
		if (pthread_create(&pthread[i], NULL, start_philo_life, &philo) != 0)
			return (free_all(&philo, pthread, 1));
		usleep(400);
		pthread_detach(pthread[i]);
		i++;
	}
	wait_until_someone_died(&philo);
	return (free_all(&philo, pthread, 0));
}
