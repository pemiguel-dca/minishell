/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 23:16:20 by pemiguel          #+#    #+#             */
/*   Updated: 2023/03/09 17:15:45 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <assert.h>
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>
# include "../libft/libft.h"
# include "../globals.h"
# include "../vector.h"

#define READ_END 0
#define WRITE_END 1

// TODO: execute relative files
typedef enum s_states
{
	ENV,
	FL,
	CMD,
	PIPED,
	APPEND,
	DELIMITER,
	OUT,
	IN
}	t_states;

typedef struct expression
{
	t_vec			args;
	t_states		state;
}	t_expression;

typedef struct parser
{
	size_t		i;
	const t_vec	*tokens;
}	t_parser;

inline static t_states	operator_type(char *op)
{
	if (ft_strcmp(op, PIPE) == 0)
		return (PIPED);
	else if (ft_strcmp(op, REDIR_APPEND) == 0)
		return (APPEND);
	else if (ft_strcmp(op, REDIR_DELIMITER) == 0)
		return (DELIMITER);
	else if (ft_strcmp(op, REDIR_OUT) == 0)
		return (OUT);
	else if (ft_strcmp(op, REDIR_IN) == 0)
		return (IN);
	assert(0);
}

/*parser.c*/
static inline bool is_operator(char *token)
{
	return (ft_strcmp(token, PIPE) == 0 || ft_strcmp(token, REDIR_APPEND) == 0
		|| ft_strcmp(token, REDIR_DELIMITER) == 0 || ft_strcmp(token, REDIR_IN) == 0
		|| ft_strcmp(token, REDIR_OUT) == 0);
}

t_vec	parse(const t_vec *tokens);
t_vec	dumb_shit(t_vec *expressions);

/*parser_utils.c*/
int	adicional_args(t_vec *expressions);
t_states	get_state(const t_vec *args);
t_vec		cmd_args(t_expression *expr);
t_vec		extra_args(t_expression *expr, t_vec *args);
t_expression	*get_new_expression(t_vec *expressions, size_t *i);
t_expression	*get_file_only(t_expression *expr);

/*spawn.c (so para ver a funcionar os comandos)*/
int			spawn(t_list *nodes, int input_fd, int output_fd);
void		redir_out(int read_fd, int *fds, int size);

/*spawn_utils.c*/
/*Verifica se existem ficheiros que devem ser criados antes de executar qualquer comando*/
int			files_to_be_created(t_list *nodes);
/*Retorna fd de file que foi criado*/
int			create_specific_file(char *file_name);
int			*create_files(t_list *head, int *size);

/*assing_env.c*/
t_list	*create_envs(char **envp);
char	**get_path_splited();


/*ADD THIS TO A NEW .H FILE PROB (+ SPAWN & SPAWN UTILS.H)*/
/*cmd_validations.c*/
char	*get_cmd_path(t_expression node);
int		is_valid_args(t_expression node);
#endif
