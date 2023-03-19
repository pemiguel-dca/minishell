/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 17:12:05 by pemiguel          #+#    #+#             */
/*   Updated: 2023/03/19 02:44:30 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

t_executer	*initialize_executer_params(t_vec *expressions)
{
	t_executer	*params;

	params = malloc(sizeof(t_executer));
	params->i = 0;
	params->input_fd = STDIN_FILENO;
	params->output_fd = STDOUT_FILENO;
	params->pos_file = 0;
	if (files_to_be_created(expressions) && params->i == 0)
		params->new_files = create_files(expressions);
	return (params);
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
