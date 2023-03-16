/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_validations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnobre-m <pnobre-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:50:00 by pemiguel          #+#    #+#             */
/*   Updated: 2023/03/16 16:10:25 by pnobre-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer.h"
#include "parser/parser.h"
#include "wait.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

char	*bin_path(t_expression expr)
{
	char		*res;
	char		*with_delim;
	char		*full_path;
	char		**path_env;
	size_t		i;

	res = NULL;
	with_delim = ft_strjoin("/", expr.args.buf[0]);
	path_env = ft_split(getenv("PATH"), ':');
	i = 0;
	while (path_env[i])
	{
		full_path = ft_strjoin(path_env[i], with_delim);
		if (access(full_path, F_OK) == 0)
		{
			res = full_path;
			break;
		}
		free(full_path);
		i++;
	}
	free(with_delim);
	return (res);
}
