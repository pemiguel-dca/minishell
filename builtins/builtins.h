/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 20:16:23 by pemiguel          #+#    #+#             */
/*   Updated: 2023/03/20 00:02:26 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

#include <stdbool.h>
# include <stdio.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include "../parser/parser.h"
# include "../lexer/lexer.h"
# include "../vector.h"

/*TODO: Separate builtins that belong to the parent*/
void	_env(t_expression *expr, t_vec *env);
void	_pwd(t_expression *expr);
void	_cd(t_expression *expr);
void	_unset(t_expression *expr, t_vec **env);

static inline bool	is_implemented_builtin(char *cmd)
{
	return (ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "unset") == 0);
		//|| ft_strcmp(cmd, "echo") == 0
		//|| ft_strcmp(cmd, "exit") == 0
		//|| ft_strcmp(cmd, "export") == 0);
}

static inline void	execute_builtin(t_expression *expr, t_vec *env)
{
	if (ft_strcmp((char *)expr->args.buf[0], "pwd") == 0)
		_pwd(expr);
	else if (ft_strcmp((char *)expr->args.buf[0], "env") == 0)
		_env(expr, env);
	else if (ft_strcmp((char *)expr->args.buf[0], "unset") == 0)
		_unset(expr, &env);
	/*
	else if (ft_strcmp((char *)expr->args.buf[0], "echo") == 0)
	else if (ft_strcmp((char *)expr->args.buf[0], "exit") == 0)
	else if (ft_strcmp((char *)expr->args.buf[0], "export") == 0)
	*/
}

#endif
