/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnobre-m <pnobre-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 18:16:24 by pnobre-m          #+#    #+#             */
/*   Updated: 2022/11/10 15:44:40 by pnobre-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "libft.h"

#define THRESHOLD '0'

int	ft_atoi(const char *nptr)
{
	bool	is_pos;
	int		i;
	int		n;

	is_pos = true;
	i = 0;
	n = 0;
	while ((nptr[i] >= 0x09 && nptr[i] <= 0x0D) || nptr[i] == 0x20)
		++i;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			is_pos = !is_pos;
		++i;
	}
	while (ft_isdigit(nptr[i]))
	{
		n = (nptr[i] - THRESHOLD) + (n * 10);
		++i;
	}
	if (!is_pos)
		n *= -1;
	return (n);
}
