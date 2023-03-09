/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnobre-m <pnobre-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 18:04:08 by pnobre-m          #+#    #+#             */
/*   Updated: 2022/11/12 19:37:39 by pnobre-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	little_len;
	size_t	i;
	size_t	j;

	little_len = ft_strlen(little);
	if (!little_len)
		return ((char *)big);
	i = 0;
	if (big || len)
	{
		while (i < ft_strlen(big) && i < len)
		{
			j = 0;
			while (little[j] && i + j < len && little[j] == big[i + j])
			{
				++j;
			}
			if (!little[j])
				return ((char *)big + i);
			++i;
		}
	}
	return (NULL);
}
