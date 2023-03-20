/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 20:34:25 by pemiguel          #+#    #+#             */
/*   Updated: 2023/03/20 22:37:58 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/*Passar envs para atualizar a variavel OLD_PWD*/

//static void	 update_pwds()

static int	change_dir_to(const t_expression *expr)
{
	struct stat	buf;
	
	if (stat(expr->args.buf[1], &buf) < 0)
	{
		printf("cd: no such file or directory: %s\n", (char *)expr->args.buf[1]);
		return (1);
	}
	else
	{
		if (S_ISDIR(buf.st_mode))
			chdir((char *)expr->args.buf[1]);
		else
		{
			printf("cd: not a directory: %s\n", (char *)expr->args.buf[1]);
			return (1);
		}
	}
	return (0);
}

int	_cd(t_expression *expr, t_vec **env)
{
	int	exit_status;
	(void)env;
	exit_status = 0;
	if (expr->args.len == 1 || ft_strcmp("~", (char *)expr->args.buf[0]) == 0)
		chdir("/home");
	else if (expr->args.len > 2)
	{
		printf("cd: too many arguments\n");
		exit_status = 1;
	}
	else if (expr->args.len == 2)
		exit_status = change_dir_to(expr);
	//if (exit_status == 0)
	//{
		
	//}
	return (exit_status);
}
