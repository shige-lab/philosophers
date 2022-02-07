#include "libft.h"

bool	is_str_int_by_atoi(int *num, char *str)
{
	if (str == NULL)
		return (false);
	*num = ft_atoi_simple(str);
	if (*str == '-' || *str == '+')
		str++;
	if (*num == 0 && !is_str_all_c(str, '0'))
		return (false);
	return (true);
}
