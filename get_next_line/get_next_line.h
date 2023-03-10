/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 14:47:08 by pemiguel          #+#    #+#             */
/*   Updated: 2023/03/10 15:08:25 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFFER_SIZE  1

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stddef.h>

size_t	ft_strlen_n(const char *str);
char	*ac_lines(int fd, char *str);
char	*next_line(char *fline);
char	*get_line_dep_buffer(char *fline);
char	*ft_strjoin_n(char *s1, char *s2);
char	*ft_strchr_n(char *str, int c);
char	*get_next_line(int fd);

#endif
