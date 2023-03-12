/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 17:24:56 by pemiguel          #+#    #+#             */
/*   Updated: 2023/03/12 15:39:38 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirs.h"

void	redir_out_append(int read_fd, int fd)
{
	char	*line;

	while (true)
	{
		line = get_next_line(read_fd);
		if (line)
			write(fd, line, ft_strlen(line));
		else
			break ;
	}
	free(line);
	close(fd);
}