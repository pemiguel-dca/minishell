/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnobre-m <pnobre-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 19:47:59 by pnobre-m          #+#    #+#             */
/*   Updated: 2022/11/12 19:13:19 by pnobre-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <limits.h>
#include "libft.h"

#define THRESHOLD '0'

void	ft_putnbr_fd(int n, int fd)
{
	char	ch;

	if (n == INT_MIN)
	{
		write(fd, "-2147483648", sizeof(char) * 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", sizeof(char));
		n *= -1;
	}
	if (n > 9)
		ft_putnbr_fd(n / 10, fd);
	ch = (n % 10) + THRESHOLD;
	write(fd, &ch, sizeof(char));
}
