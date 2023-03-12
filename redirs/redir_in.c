/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:20:26 by pemiguel          #+#    #+#             */
/*   Updated: 2023/03/12 17:20:37 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirs.h"
/*do tomorrow*/
void	redir_in(int read_fd, char *file_name)
{
	int	fd;

	printf("%s", file_name);
	fd = open(file_name, O_RDONLY);	
	if (fd < 0)
	{
		printf("%s : No such file or directory", file_name);
	}
}