/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 16:04:36 by pemiguel          #+#    #+#             */
/*   Updated: 2023/04/13 15:59:34 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

# include <assert.h>
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include "../env_vars/env.h"
# include "../libft/libft.h"
# include "../globals.h"
# include "../vector.h"
# include "../parser/parser.h"
# include "../redirs/redirs.h"
# include "../builtins/builtins.h"
# include "../get_next_line/get_next_line.h"

extern t_signals	g_signals;

# define READ_END 0
# define WRITE_END 1

/*executer.c*/

/*Where the magic happens*/
int					executer(t_vec *expressions,
						t_executer *params, t_vec *env);

static inline char	*file(t_vec *expressions, size_t i)
{
	t_expression	*expr;

	expr = expressions->buf[i];
	return (expr->args.buf[0]);
}

static inline void	close_file_descriptors(t_executer *params)
{
	if (params->input_fd != STDIN_FILENO)
		close(params->input_fd);
	if (params->output_fd != STDOUT_FILENO)
		close(params->output_fd);
}

static inline bool	is_binary(char *arg)
{
	bool	res;

	res = false;
	if (arg[0] == '.' && arg[1] == '/')
		res = true;
	else if (arg[0] == '/')
		res = true;
	return (res);
}

/*executer_utils.c*/

/*Initialize all the paramaters needed for executer*/
t_executer			*initialize_executer_params(t_vec *expressions,
						size_t executer_res);
/*Searches for binary path*/
char				*bin_path(t_expression *expr, t_vec *env);
/*Execute a specific command*/
void				execute_cmd(t_expression *expr, t_vec *env,
						char *path);

#endif
