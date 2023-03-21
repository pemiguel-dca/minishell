/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 20:34:25 by pemiguel          #+#    #+#             */
/*   Updated: 2023/03/21 14:51:23 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/*Passar envs para atualizar a variavel OLD_PWD*/

static void	 update_pwds(t_vec **env, char *new_oldpwd, char *new_pwd)
{
	
}

static int	change_dir_to(const char *path)
{
	struct stat	buf;

	if (stat(path, &buf) < 0)
	{
		printf("cd: no such file or directory: %s\n", path);
		return (1);
	}
	else
	{
		if (S_ISDIR(buf.st_mode))
			chdir(path);
		else
		{
			printf("cd: not a directory: %s\n", path);
			return (1);
		}
	}
	return (0);
}

static int	go_home(t_vec *env)
{
	int	pos_home;
	int	exit_status;

	pos_home = pos_env_var(env, "HOME");
	exit_status = 0;
	if (pos_home == -1)
	{
		printf("cd: HOME not set\n");
		exit_status = 1;
	}
	else
		exit_status = change_dir_to(env->buf[pos_home] + 5);
	return (exit_status);
}

int	_cd(t_expression *expr, t_vec **env)
{
	int		exit_status;
	(void)env;
	exit_status = 0;
	if (expr->args.len == 1 || ft_strcmp("~", (char *)expr->args.buf[0]) == 0)
		exit_status = go_home(*env);
	else if (expr->args.len > 2)
	{
		printf("cd: too many arguments\n");
		exit_status = 1;
	}
	else if (expr->args.len == 2)
		exit_status = change_dir_to(expr->args.buf[1]);
	//if (exit_status == 0)
	//{

	//}
	return (exit_status);
}
