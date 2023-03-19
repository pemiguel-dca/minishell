/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 16:04:36 by pemiguel          #+#    #+#             */
/*   Updated: 2023/03/19 15:17:45 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

# include <assert.h>
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>
# include "../libft/libft.h"
# include "../globals.h"
# include "../vector.h"
# include "../parser/parser.h"
# include "../redirs/redirs.h"
# include "../builtins/builtins.h"
# include "../get_next_line/get_next_line.h"

# define READ_END 0
# define WRITE_END 1

typedef struct executer
{
	size_t	i;
	int		input_fd;
	int		output_fd;
	int		pipe_fd[2];
	int		*new_files;
	size_t	pos_file;
}	t_executer;

/*executer.c*/

/*Where the magic happens*/
int					executer(t_vec *expressions, t_executer *params, t_vec *env);

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

/*executer_utils.c*/

/*Initialize all the paramaters needed for executer*/
t_executer			*initialize_executer_params(t_vec *expressions);
/*Searchs for binary path*/
char				*bin_path(t_expression expr);
/*Execute a specific command*/
void				execute_cmd(t_expression *expr, t_vec *env);

#endif
