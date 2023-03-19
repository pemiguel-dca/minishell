/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 16:04:36 by pemiguel          #+#    #+#             */
/*   Updated: 2023/03/19 00:00:10 by pemiguel         ###   ########.fr       */
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
# include "../get_next_line/get_next_line.h"

#define READ_END 0
#define WRITE_END 1

/*Para o executer em geral (só uma maneira de encurtar código)*/
typedef struct	executer
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
int		executer(t_vec *expressions, t_executer *params);

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

/*Checks if there's any files that need to be created*/
int		files_to_be_created(t_vec *expressions);
/*Retorna fd de file que foi criado*/
int		create_specific_file(char *file_name, t_states action);
/*Returns an array with all the new files that need to be created*/
int		*create_files(t_vec *expressions);
/*Searchs for binary path*/
char	*bin_path(t_expression expr);
/*Execute a specific command*/
void	execute_cmd(t_expression *expr);

#endif
