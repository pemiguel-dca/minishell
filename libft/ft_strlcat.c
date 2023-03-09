/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnobre-m <pnobre-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 15:11:26 by pnobre-m          #+#    #+#             */
/*   Updated: 2022/11/12 19:19:53 by pnobre-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dst_len;

	if (dst)
		dst_len = ft_strlen(dst);
	else
		dst_len = 0;
	if (size < dst_len)
		return (size + ft_strlen(src));
	if (size)
	{
		i = 0;
		while (src[i] && dst_len + i < size - 1)
		{
			dst[dst_len + i] = src[i];
			++i;
		}
		dst[dst_len + i] = '\0';
	}
	return (dst_len + ft_strlen(src));
}
