/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:48:36 by pemiguel          #+#    #+#             */
/*   Updated: 2023/03/12 15:42:26 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer.h"
#include "parser/parser.h"
#include "wait.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
//#include "get_next_line/get_next_line.h"

int	files_to_be_created(t_vec *expressions)
{
	t_expression	*expr;
	size_t			i;

	i = 0;
	while (i < expressions->len)
	{
		expr = (t_expression *)expressions->buf[i];
		if (expr->state == OUT || expr->state == APPEND)
			return (1);
		i += 1;
	}
	return (0);
}

int	create_specific_file(char *file_name, t_states state)
{
	int			fd;
	struct stat sb;
	
	if (state == APPEND && stat(file_name, &sb) == 0)
		fd = open(file_name, O_WRONLY | O_APPEND, 0644);
	else
		fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		printf("Could not open file\n");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

int	*create_files(t_vec *expressions)
{
	t_expression	*expr;
	t_expression	*prev_expr;
	int				*file_descriptors;
	size_t			i;
	size_t			j;

	prev_expr = NULL;
	file_descriptors = malloc(100 * sizeof(int));
	i = 0;
	j = 0;
	while (j < expressions->len)
	{
		expr = (t_expression *)expressions->buf[j];
		if (expr->state == FL && prev_expr)
		{
			file_descriptors[i] = create_specific_file(expr->args.buf[0], prev_expr->state);
			i += 1;
		}
		if (j + 1 != expressions->len && ((t_expression *)expressions->buf[j + 1])->state == FL)
			prev_expr = expr;
		j += 1;
	}
	file_descriptors[i] = 0;
	return (file_descriptors);
}
