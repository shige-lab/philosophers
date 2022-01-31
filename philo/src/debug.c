#include "philo.h"

void	debug_philo(t_philo *philo)
{
	printf("philo->th_num = %d\n", philo->th_num);
	printf("philo->eat_time = %d\n", philo->eat_time);
	printf("philo->die_time = %d\n", philo->die_time);
	printf("philo->sleep_time = %d\n", philo->sleep_time);
	printf("philo->eat_limit = %d\n", philo->eat_limit);
}
