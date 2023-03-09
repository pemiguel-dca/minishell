/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnobre-m <pnobre-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:34:42 by pnobre-m          #+#    #+#             */
/*   Updated: 2022/11/09 20:41:56 by pnobre-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>
#include "libft.h"

#define THRESHOLD '0'

static unsigned int	ft_int_len(int n)
{
	long			l_n;
	unsigned int	len;

	l_n = n;
	len = 1;
	if (l_n < 0)
	{
		++len;
		l_n *= -1;
	}
	while (l_n > 9)
	{
		++len;
		l_n /= 10;
	}
	return (len);
}

static void	ft_put_nbr(char *buf, int *n, size_t cursor)
{
	int	ch;

	ch = (*n % 10) + THRESHOLD;
	if (*n > 9)
	{
		*n /= 10;
		ft_put_nbr(buf, n, cursor - 1);
	}
	buf[cursor] = ch;
}

char	*ft_itoa(int n)
{
	unsigned int	len;
	char			*buf;

	len = ft_int_len(n);
	buf = malloc(sizeof(char) * (len + 1));
	if (!buf)
		return (NULL);
	if (n == INT_MIN)
	{
		ft_strlcpy(buf, "-2147483648", len + 1);
	}
	else
	{
		if (n < 0)
		{
			buf[0] = '-';
			n *= -1;
			ft_put_nbr(buf, &n, len - 1);
		}
		else
			ft_put_nbr(buf, &n, len - 1);
	}
	buf[len] = '\0';
	return (buf);
}
