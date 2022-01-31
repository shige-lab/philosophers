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
//	size_t	th_num;
//	size_t	eat_time;
//	size_t	die_time;
//	size_t	sleep_time;
//}	t_data;

typedef struct s_philo
{
	bool			is_dead;
	int				num_x;
	int				th_num;
	int				eat_time;
	int				die_time;
	int				sleep_time;
	int				eat_limit;
	size_t			*last_eat;
	pthread_mutex_t	*fork;
	pthread_mutex_t	log;
	pthread_mutex_t	_num_x;
}	t_philo;

size_t	get_left_index(size_t th_num, size_t rihgt_index);
size_t	get_current_time(void);
void	put_log(pthread_mutex_t *log, char *action, size_t th_index);

int		eating(t_philo *philo, size_t th_index);
void	init_last_eat(t_philo *philo, size_t th_num);
void	action_time(size_t time);
void	set_num_x(t_philo *philo);
bool	can_get_forks(t_philo *philo, size_t th_index);

// philo.c
int		init_t_philo(t_philo *philo);
void	*start_philo_life(void *p);

// debug.c
void	debug_philo(t_philo *philo);

#endif
