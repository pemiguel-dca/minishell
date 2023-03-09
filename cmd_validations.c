/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_validations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:50:00 by pemiguel          #+#    #+#             */
/*   Updated: 2023/03/07 21:50:43 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer.h"
#include "parser/parser.h"
#include "wait.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

char	*get_cmd_path(t_expression node)
{
	char	**path;
	struct stat sb;
	char	*cmd_path;
	size_t	i;

	path = get_path_splited();
	i = 0;
	while (path[i])
	{
		if (stat(ft_strjoin(path[i], ft_strjoin("/", node.args[0])), &sb) == 0)
			break ;
		i++;
	}
	cmd_path = ft_strdup(ft_strjoin(path[i], ft_strjoin("/", node.args[0])));
	return (cmd_path);
}

int	is_valid_args(t_expression node)
{
	char	**path;
	struct stat sb;
	int		exists;
	size_t	i;

	path = get_path_splited();
	exists = 0;
	i = 0;
	while (path[i])
	{
		if (stat(ft_strjoin(path[i], ft_strjoin("/", node.args[0])), &sb) == 0)
			exists = 1;
		i++;
	}
	return (exists);
}
