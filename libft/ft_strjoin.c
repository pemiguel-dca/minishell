/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:58:29 by pnobre-m          #+#    #+#             */
/*   Updated: 2023/02/26 18:14:35 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*buf;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	buf = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!buf)
		return (NULL);
	ft_strlcpy(buf, s1, s1_len + 1);
	ft_strlcpy(buf + s1_len, s2, s2_len + 1);
	return (buf);
}
