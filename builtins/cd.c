/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 20:34:25 by pemiguel          #+#    #+#             */
/*   Updated: 2023/03/22 22:18:46 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	go_to_oldpwd(t_vec *env)
{
	int	i;
	int	exit_status;

	i = pos_env_var(env, "OLDPWD");
	exit_status = 0;
	if (i == -1)
	{
		printf("cd: OLDPWD not set\n");
		exit_status = 1;
	}
	else
		exit_status = change_dir_to(env->buf[i] + 7, env);
	return (exit_status);
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
		exit_status = change_dir_to(env->buf[pos_home] + 5, env);
	return (exit_status);
}

int	change_dir_to(const char *path, t_vec *env)
{
	struct stat	buf;
	int			exit_status;

	exit_status = 0;
	if (ft_strcmp("-", (char *)path) == 0)
		exit_status = go_to_oldpwd(env);
	else if (stat(path, &buf) < 0)
	{
		printf("cd: no such file or directory: %s\n", path);
		exit_status = 1;
	}
	else
	{
		if (S_ISDIR(buf.st_mode))
			chdir(path);
		else
		{
			printf("cd: not a directory: %s\n", path);
			exit_status = 1;
		}
	}
	return (exit_status);
}

static void	set_pwds(t_expression *expr, char *curr_pwd, t_vec *env)
{
	char	*new_pwd;

	new_pwd = NULL;
	if (expr->args.len == 1)
		set_env(&env, "PWD", env->buf[pos_env_var(env, "HOME") + 5]);
	else if (ft_strcmp("..", (char *)expr->args.buf[1]) == 0)
	{
		new_pwd = get_path_before(curr_pwd);
		set_env(&env, "PWD", new_pwd);
	}
	else
	{
		new_pwd = ft_strjoin(env->buf[pos_env_var(env, "PWD")], (char *)expr->args.buf[1]);
		set_env(&env, "PWD", new_pwd);
	}
	set_env(&env, "OLDPWD", curr_pwd);
	free(new_pwd);
}

size_t	_cd(t_expression *expr, t_vec *env)
{
	int		exit_status;
	char	curr_pwd[PATH_MAX];

	getcwd(curr_pwd, PATH_MAX);
	exit_status = 0;
	if (expr->args.len == 1 || ft_strcmp("~", (char *)expr->args.buf[0]) == 0)
		exit_status = go_home(env);
	else if (expr->args.len > 2)
	{
		printf("cd: too many arguments\n");
		exit_status = 1;
	}
	else if (expr->args.len == 2)
		exit_status = change_dir_to(expr->args.buf[1], env);
	if (exit_status == 0)
		set_pwds(expr, curr_pwd, env);
	return (exit_status);
}

