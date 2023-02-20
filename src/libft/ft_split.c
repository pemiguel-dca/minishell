/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnobre-m <pnobre-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 20:07:09 by pnobre-m          #+#    #+#             */
/*   Updated: 2022/12/07 20:14:50 by pnobre-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include "libft.h"

static size_t	ft_split_n(char const *s, char c)
{
	bool	flag;
	size_t	len;
	size_t	i;
	size_t	n;

	flag = true;
	len = ft_strlen(s);
	i = 0;
	n = 0;
	while (i < len)
	{
		if (s[i] == c && !flag)
		{
			flag = true;
		}
		else if (s[i] != c && flag)
		{
			flag = false;
			++n;
		}
		++i;
	}
	return (n);
}

static void	ft_next_str(char *s, char c, char	**buf, size_t i)
{
	char	*next;

	while (*s == c)
		++s;
	next = ft_strchr(s, c);
	if (!next)
		buf[i] = ft_strdup(s);
	else
	{
		buf[i] = ft_substr(s, 0, next - s);
		s += next - s;
		if (*s && s[1])
			ft_next_str(s, c, buf, i + 1);
	}
}

char	**ft_split(char const *s, char c)
{
	size_t	occurrences;
	char	**buf;

	if (!s)
		return (NULL);
	occurrences = ft_split_n(s, c);
	buf = malloc(sizeof(char *) * (occurrences + 1));
	if (!buf)
		return (NULL);
	ft_next_str((char *)s, c, buf, 0);
	buf[occurrences] = NULL;
	return (buf);
}
