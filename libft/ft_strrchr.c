/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnobre-m <pnobre-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 16:32:35 by pnobre-m          #+#    #+#             */
/*   Updated: 2022/11/04 15:56:54 by pnobre-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*last;
	char	*i;

	last = NULL;
	i = (char *)s;
	if (c == '\0')
		return ((char *)s + ft_strlen(s));
	while (*i || !c)
	{
		if (*i == c)
			last = i;
		++i;
	}
	return (last);
}
