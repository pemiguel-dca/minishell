/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnobre-m <pnobre-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 20:34:25 by pemiguel          #+#    #+#             */
/*   Updated: 2023/03/02 16:54:15 by pnobre-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	_cd(t_parser *parser)
{
	struct stat	buf;

	if (ft_arraystrlen(parser->args) == 1
		|| ft_strcmp("~", parser->args[1]) == 0)
		chdir("/home");
	else if (ft_arraystrlen(parser->args) > 2)
		printf("cd: string not in pwd: %s\n", parser->args[1]);
	else if (ft_arraystrlen(parser->args) == 2)
	{
		if (stat(parser->args[1], &buf) < 0)
			printf("cd: no such file or directory: %s\n", parser->args[1]);
		else
		{
			if (S_ISDIR(buf.st_mode))
				chdir(parser->args[1]);
			else
				printf("cd: not a directory: %s\n", parser->args[1]);
		}
	}
	return (0);
}
