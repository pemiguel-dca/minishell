/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnobre-m <pnobre-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 02:42:07 by pemiguel          #+#    #+#             */
/*   Updated: 2023/03/22 18:52:42 by pnobre-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirs.h"

int	files_to_be_created(t_vec *expressions)
{
	t_expression	*expr;
	size_t			i;
	int				count_files;

	i = 0;
	count_files = 0;
	while (i < expressions->len)
	{
		expr = (t_expression *)expressions->buf[i];
		if (expr->state == OUT || expr->state == APPEND)
			count_files++;
		i += 1;
	}
	return (count_files);
}

int	create_specific_file(char *file_name, t_states state)
{
	int			fd;
	struct stat	sb;

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
	t_expression	*prev;
	int				*files;
	size_t			i;
	size_t			j;

	files = malloc(files_to_be_created(expressions) * sizeof(int));
	i = 0;
	j = 0;
	while (j < expressions->len)
	{
		expr = (t_expression *)expressions->buf[j];
		if (expr->state == FL && (prev->state == OUT || prev->state == APPEND))
		{
			files[i] = create_specific_file(expr->args->buf[0], prev->state);
			i += 1;
		}
		if (j + 1 != expressions->len
			&& ((t_expression *)expressions->buf[j + 1])->state == FL)
			prev = expr;
		j += 1;
	}
	files[i] = 0;
	return (files);
}
