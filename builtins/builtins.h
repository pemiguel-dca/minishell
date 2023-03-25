/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 20:16:23 by pemiguel          #+#    #+#             */
/*   Updated: 2023/03/24 14:47:55 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <linux/limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include "../env_vars/env.h"
# include "../parser/parser.h"
# include "../libft/libft.h"
# include "../lexer/lexer.h"
# include "../vector.h"

size_t	_env(t_expression *expr, t_vec *env);
size_t	_pwd(t_expression *expr);
size_t	_cd(t_expression *expr, t_vec *env);
size_t	_unset(t_expression *expr, t_vec **env);
size_t	_export(t_expression *expr, t_vec *env);
size_t	_echo(t_expression *expr);
void	mini_exit(t_expression *expr, t_executer *params);

static inline bool	is_child_builtin(char *cmd)
{
	return (ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "echo") == 0);
}

static inline bool	is_parent_builtin(char *cmd)
{
	return (ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "exit") == 0);
}

int	change_dir_to(const char *path, t_vec *env);

static inline char	*get_path_before(char *curr_path)
{
	size_t	i;
	char	*path_before;

	i = ft_strlen(curr_path) - 1;
	while (i != 0 && curr_path[i] != '/')
		i -= 1;
	path_before = ft_substr(curr_path, 0, i);
	return (path_before);
}

static inline void	execute_child_builtin(t_expression *expr, t_vec *env, t_executer *params)
{
	if (ft_strcmp((char *)expr->args.buf[0], "pwd") == 0)
		params->exit_status = _pwd(expr);
	else if (ft_strcmp((char *)expr->args.buf[0], "env") == 0)
		params->exit_status = _env(expr, env);
	else if (ft_strcmp((char *)expr->args.buf[0], "echo") == 0)
		params->exit_status = _echo(expr);
}

static inline void	execute_parent_builtin(t_expression *expr, t_vec *env, t_executer *params)
{
	if (ft_strcmp((char *)expr->args.buf[0], "cd") == 0)
		params->exit_status = _cd(expr, env);
	else if (ft_strcmp((char *)expr->args.buf[0], "unset") == 0)
		params->exit_status = _unset(expr, &env);
	else if (ft_strcmp((char *)expr->args.buf[0], "export") == 0)
		params->exit_status = _export(expr, env);
	else if (ft_strcmp((char *)expr->args.buf[0], "exit") == 0)
		mini_exit(expr, params);
}

#endif
