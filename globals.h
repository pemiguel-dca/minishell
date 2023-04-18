/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnobre-m <pnobre-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 16:51:23 by pnobre-m          #+#    #+#             */
/*   Updated: 2023/04/18 18:35:48 by pnobre-m         ###   ########.fr       */
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

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdint.h>

typedef struct signals
{
	pid_t		pid;
	bool		pressed_in_child;
	long long	exit_status;
	bool		is_heredoc;
}	t_signals;

typedef struct executer
{
	size_t		i;
	int			input_fd;
	int			output_fd;
	int			heredoc_fd;
	char		**delims;
	int			pipe_fd[2];
	int			*new_files;
	size_t		exit;
	size_t		pos_file;
}	t_executer;

typedef struct token
{
	bool	known_literal;
	char	*s;
}	t_token;

void	sig_int(int n);
void	ignore_signal(int n);

#endif
