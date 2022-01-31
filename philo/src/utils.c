#include "philo.h"

size_t	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

size_t	get_left_index(size_t pthread_num, size_t rihgt_index)
{
	if (rihgt_index == 0)
		return (pthread_num - 1);
	return (rihgt_index - 1);
}

void	put_log(pthread_mutex_t *log, char *action, size_t pthread_index)
{
	while (true)
	{
		if (pthread_mutex_lock(log) == 0)
			break ;
	}
	printf("%zu %zu %s\n", get_current_time(), pthread_index + 1, action);
	pthread_mutex_unlock(log);
}

void	action_time(size_t time)
{
	size_t	start;

	start = get_current_time();
	while (get_current_time() - start < time)
		usleep(100);
}
