/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin_and_free_null.c                             :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: tshigena <tshigena@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 16:40:59 by tshigena          #+#    #+#             */
/*   Updated: 2022/01/11 16:54:46 by tshigena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*strjoin_and_free(char *s1, char *s2)
{
	char	*total;
	size_t	len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	total = (char *)malloc((len + 1) * sizeof(char));
	if (total)
	{
		ft_strlcpy(total, s1, ft_strlen(s1) + 1);
		ft_strlcat(total, s2, len + 1);
	}
	free(s1);
	free(s2);
	if (total == NULL)
		return (NULL);
	return (total);
}
