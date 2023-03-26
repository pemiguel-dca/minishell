/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 16:51:23 by pnobre-m          #+#    #+#             */
/*   Updated: 2023/03/26 17:31:38 by pemiguel         ###   ########.fr       */
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

# include <stdbool.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>

typedef struct signals
{
	bool		sig_int;
	bool		sig_quit;
	int			pid;
	long long	exit_status;
}	t_signals;

typedef struct executer
{
	size_t		i;
	int			input_fd;
	int			output_fd;
	int			pipe_fd[2];
	int			*new_files;
	size_t		exit;
	long long	exit_status;
	size_t		pos_file;
}	t_executer;

void	sig_int(int n);
void	sig_quit(int n);

#endif
