/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:20:26 by pemiguel          #+#    #+#             */
/*   Updated: 2023/03/13 15:55:07 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirs.h"

void	redir_in(int read_fd, char *file_name)
{
	int	fd;
	int	saved_fd;

	fd = open(file_name, O_RDONLY);
	saved_fd = dup(read_fd);
	if (fd < 0)
	{
		printf("%s : No such file or directory\n", file_name);
		exit(EXIT_FAILURE);
	}
}
