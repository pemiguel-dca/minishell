/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 17:24:30 by pemiguel          #+#    #+#             */
/*   Updated: 2023/03/12 16:26:28 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer/lexer.h"
#include "../parser/parser.h"
#include "wait.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include "../get_next_line/get_next_line.h"

void	redir_out_append(int read_fd, int fd);
void    redir_in(int read_fd, char *file_name);