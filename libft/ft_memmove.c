/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnobre-m <pnobre-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:08:40 by pnobre-m          #+#    #+#             */
/*   Updated: 2022/11/10 15:40:39 by pnobre-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdint.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	j;

	if (dest || src)
	{
		if (src < dest)
		{
			while (n)
			{
				--n;
				((uint8_t *)dest)[n] = ((uint8_t *)src)[n];
			}
		}
		else
		{
			j = 0;
			while (j < n)
			{
				((uint8_t *)dest)[j] = ((uint8_t *)src)[j];
				++j;
			}
		}
	}
	return (dest);
}
