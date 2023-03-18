/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 16:04:36 by pemiguel          #+#    #+#             */
/*   Updated: 2023/03/18 17:49:57 by pemiguel         ###   ########.fr       */
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

typedef struct	s_files
{
	int		*new_files;
	size_t	pos_file;
	int		read_file;
}	t_files;

int		executer(t_vec *expressions, int input_fd, int output_fd);

/*Verifica se existem ficheiros que devem ser criados antes de executar qualquer comando*/
int		files_to_be_created(t_vec *expressions);
/*Retorna fd de file que foi criado*/
int		create_specific_file(char *file_name, t_states action);
/*Retorna um array com todos os ficheiros que vao ser criados*/
int		*create_files(t_vec *expressions);
/*Searchs for binary path*/
char	*bin_path(t_expression expr);

#endif
