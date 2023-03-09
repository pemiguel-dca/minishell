/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 17:24:56 by pemiguel          #+#    #+#             */
/*   Updated: 2023/03/06 17:25:30 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirs.h"

/*Preety much done*/
void	redir_out(int read_fd, int *fds, int size)
{
	char	*line;
	size_t	i;

	i = 0;
	line = get_next_line(read_fd);
	while (line)
	{
		i = 0;
		while (i < size)
		{
			write(fds[i], line, ft_strlen(line));
			++i;
		}
		line = get_next_line(read_fd);
	}
	free(line);
	i = 0;
	while (i < size)
		close(fds[i++]);
}