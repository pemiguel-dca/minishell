/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 20:34:25 by pemiguel          #+#    #+#             */
/*   Updated: 2023/03/20 00:01:04 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/*Passar envs para atualizar a variavel OLD_PWD*/
void	_cd(t_expression *expr)
{
	struct stat	buf;

	if (expr->args.len == 1 || ft_strcmp("~", (char *)expr->args.buf[0]) == 0)
		chdir("/home");
	else if (expr->args.len > 2)
		printf("cd: too many arguments\n");
	else if (expr->args.len == 2)
	{
		if (stat(expr->args.buf[1], &buf) < 0)
			printf("cd: no such file or directory: %s\n", (char *)expr->args.buf[1]);
		else
		{
			if (S_ISDIR(buf.st_mode))
				chdir((char *)expr->args.buf[1]);
			else
				printf("cd: not a directory: %s\n", (char *)expr->args.buf[1]);
		}
	}
}
