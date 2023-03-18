/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 17:24:30 by pemiguel          #+#    #+#             */
/*   Updated: 2023/03/18 20:08:24 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer/lexer.h"
#include "../parser/parser.h"
#include "wait.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include "../get_next_line/get_next_line.h"

/*redir_out.c*/

/*Redirs output or append*/
void	redir_out_append(int read_fd, int fd);
/*Checks if current 'redir out or append' are the last in the expression*/
int		last_out_append(t_vec *expressions, size_t i);
/*Get the position of the file in the array of new_files*/
size_t	get_pos_fd(t_vec *expressions, size_t i);

/*redir_in.c*/

/*Read from file descriptor*/
int		read_fd(char *file_name);
/*Verifies if you actually need to redir input.
The only case where we will have to redirect input is when the command has more than one argument and none of that extra argument is a flag '-'*/
int		theres_a_need_to_redir(t_vec *expressions, size_t i);
/*Checks cmd arguments to see if there's a flag*/
int		check_cmd_args(t_expression *expr);
/*Returns how many times that 'i' as to skip to ignore useless case of redir input*/
int		times_in(t_vec *expressions, size_t i);
/*Checks if current 'redir in' is the last in the expression*/
int		last_in(t_vec *expressions, size_t i);
