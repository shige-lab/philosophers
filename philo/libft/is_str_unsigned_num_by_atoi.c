#include "libft.h"

bool	is_str_unsigned_num_by_atoi(int *num, char *str)
{
	return (is_str_int_by_atoi(num, str) == true && *num >= 0);
}
