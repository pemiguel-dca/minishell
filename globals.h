/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 16:51:23 by pnobre-m          #+#    #+#             */
/*   Updated: 2023/03/19 14:28:53 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBALS_H
# define GLOBALS_H

# define COLOR_BOLD "\e[1m"
# define COLOR_CYAN "\x1b[36m"
# define COLOR_OFF  "\e[m"

# define LIT_REDIR_OUT ">"
# define LIT_REDIR_IN "<"
# define LIT_REDIR_APPEND ">>"
# define LIT_REDIR_DEL "<<"
# define LIT_PIPE "|"

# define LIT_QUOTE '\''
# define LIT_DOUBLE_QUOTE '"'

# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>

#endif
