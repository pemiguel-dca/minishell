/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnobre-m <pnobre-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:38:32 by pnobre-m          #+#    #+#             */
/*   Updated: 2022/11/10 15:16:33 by pnobre-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	init;
	size_t	end;

	if (!s1)
		return (NULL);
	init = 0;
	while (ft_strchr(set, s1[init]))
		++init;
	end = ft_strlen(s1);
	while (ft_strrchr(set, s1[end]))
		--end;
	return (ft_substr(s1, init, end - init + 1));
}
