/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 17:12:05 by pemiguel          #+#    #+#             */
/*   Updated: 2023/03/18 23:52:17 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

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
		if (expr->state == FL && (prev_expr->state == OUT || prev_expr->state == APPEND))
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

char	*bin_path(t_expression expr)
{
	char		*res;
	char		*with_delim;
	char		*full_path;
	char		**path_env;
	size_t		i;

	res = NULL;
	with_delim = ft_strjoin("/", expr.args.buf[0]);
	path_env = ft_split(getenv("PATH"), ':');
	i = 0;
	while (path_env[i])
	{
		full_path = ft_strjoin(path_env[i], with_delim);
		if (access(full_path, F_OK) == 0)
		{
			res = full_path;
			break ;
		}
		free(full_path);
		i++;
	}
	free(with_delim);
	return (res);
}

void	execute_cmd(t_expression *expr)
{
	char	*path;

	path = bin_path(*expr);
	if (path)
	{
		vec_push(&expr->args, 0);
		execve(path, (char **)expr->args.buf, NULL);
	}
	else
	{
		printf("Command not found: %s\n", (char *)expr->args.buf[0]);
		exit(EXIT_FAILURE);
	}
	free(path);
}
