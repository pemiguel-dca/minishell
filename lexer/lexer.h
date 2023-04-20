/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnobre-m <pnobre-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 22:28:38 by pedro             #+#    #+#             */
/*   Updated: 2023/04/20 16:02:16 by pnobre-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdbool.h>
# include "../globals.h"
# include "../vector.h"
# include "../libft/libft.h"

extern t_signals	g_signals;

typedef struct lexer
{
	size_t		i;
	const char	*input;
}	t_lexer;

inline static char	*l_curr(const t_lexer *lexer, size_t i)
{
	return ((char *)lexer->input + i);
}

inline static bool	is_redir(const char *token)
{
	return (ft_strcmp((char *)token, LIT_REDIR_APPEND) == 0
		|| ft_strcmp((char *)token, LIT_REDIR_DEL) == 0
		|| ft_strcmp((char *)token, LIT_REDIR_IN) == 0
		|| ft_strcmp((char *)token, LIT_REDIR_OUT) == 0);
}

static inline bool	is_last_status(char *arg)
{
	return (ft_strncmp("$?", arg, 2) == 0);
}

t_vec	trim_empty(t_vec tokens);

t_vec	tokenize(t_vec *env, const char *buf);

char	*expand_token(const char *token, t_vec *env);

t_vec	rearrange_tokens(t_vec *tokens);

char	*join_next(t_lexer *lexer,
						const char *token,
						t_vec *env,
						bool is_quoted);

t_token	*get_next(t_vec *env, t_lexer *lexer);

#endif
