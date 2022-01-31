/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshigena <tshigena@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 21:52:19 by tshigena          #+#    #+#             */
/*   Updated: 2022/01/04 22:37:38 by tshigena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include "../libft/libft.h"

# define ERROR -1
//typedef struct s_data
//{
//	size_t	pthread_num;
//	size_t	eat_time;
//	size_t	die_time;
//	size_t	sleep_time;
//}	t_data;

typedef struct s_philo
{
	bool			is_dead;
	size_t			num_x;
//	t_data			data;
	size_t	pthread_num;
	size_t	eat_time;
	size_t	die_time;
	size_t	sleep_time;
	size_t	*last_eat;
	pthread_mutex_t	*fork;
//	pthread_mutex_t	act;
	pthread_mutex_t	log;
	pthread_mutex_t	_num_x;
}	t_philo;

size_t	get_left_index(size_t pthread_num, size_t rihgt_index);
size_t	get_current_time(void);
void	put_log(pthread_mutex_t *log, char *action, size_t pthread_index);

int		eating(t_philo *philo, size_t pthread_index);
void	init_last_eat(t_philo *philo, size_t pthread_num);
void	action_time(size_t time);
void	set_num_x(t_philo *philo);

// philo.c
int		init_t_philo(t_philo *philo);
void	*start_philo_life(void *p);

#endif
