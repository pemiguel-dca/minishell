/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:48:36 by pemiguel          #+#    #+#             */
/*   Updated: 2023/03/07 21:50:43 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer.h"
#include "parser/parser.h"
#include "wait.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line/get_next_line.h"

int	files_to_be_created(t_list *head)
{
	t_expression	*node;

	while (head)
	{
		node = ((t_expression *)head->content);
		if (node->state == OUT || node->state == APPEND)
			return (1);
		head = head->next;
	}
	return (0);
}

int	create_specific_file(char *file_name)
{
	int	fd;

	fd  = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		printf("Could not open file\n");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

int	*create_files(t_list *head, int *size)
{
	t_expression	*node;
	t_expression	*prev_node;
	int		*file_descriptors;
	size_t	i;

	prev_node = NULL;
	file_descriptors = malloc(100 * sizeof(int));
	i = 0;
	while (head)
	{
		node = ((t_expression *)head->content);
		if (node->state == FL && prev_node)//deal with APPEND in a diferent way
		{
			file_descriptors[i] = create_specific_file(node->args[0]);
			++i;
			*size+= 1;
		}
		if (head->next && ((t_expression *)((t_list *)head->next)->content)->state == OUT
			|| head->next && ((t_expression *)((t_list *)head->next)->content)->state == APPEND)
			prev_node = node;
		head = head->next;
	}
	file_descriptors[i] = 0;
	return (file_descriptors);
}
