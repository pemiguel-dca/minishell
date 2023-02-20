/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnobre-m <pnobre-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 22:57:22 by pedro             #+#    #+#             */
/*   Updated: 2022/12/01 16:25:54 by pnobre-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "get_next_line.h"

static char	*trunc_from_global(char **global_buf)
{
	char	*split;
	char	*popped;
	char	*rem;

	split = ft_strchr(*global_buf, '\n') + 1;
	popped = ft_substr(*global_buf, 0, split - *global_buf);
	rem = ft_strdup(split);
	free(*global_buf);
	*global_buf = rem;
	return (popped);
}

static void	push_to_global(char *buf, char **global_buf)
{
	char	*dup;

	if (*global_buf)
	{
		dup = ft_strjoin(*global_buf, buf);
		free(*global_buf);
		*global_buf = dup;
	}
	else
	{
		*global_buf = ft_strdup(buf);
	}
}

static void	read_to_buf(int fd, char **global_buf)
{
	char	*buf;
	ssize_t	n;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return ;
	while (1)
	{
		n = read(fd, buf, BUFFER_SIZE);
		if (n == -1 || (!n && (!*global_buf || !**global_buf)))
		{
			if (*global_buf)
			{
				free(*global_buf);
				*global_buf = NULL;
			}
			free(buf);
			return ;
		}
		buf[n] = '\0';
		push_to_global(buf, global_buf);
		if (!(n == BUFFER_SIZE && !ft_strchr(*global_buf, '\n')))
			break ;
	}
	free(buf);
}

char	*get_next_line(int fd)
{
	static char	*global_buf;
	char		*dup;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_to_buf(fd, &global_buf);
	if (global_buf)
	{
		if (ft_strchr(global_buf, '\n'))
		{
			return (trunc_from_global(&global_buf));
		}
		else
		{
			dup = ft_strdup(global_buf);
			free(global_buf);
			global_buf = NULL;
			return (dup);
		}
	}
	return (NULL);
}
