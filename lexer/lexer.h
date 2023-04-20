/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 22:28:38 by pedro             #+#    #+#             */
/*   Updated: 2023/04/20 18:02:26 by pemiguel         ###   ########.fr       */
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

char	*dispatch_normal(t_lexer *lexer, size_t i, t_vec *env);

char	*dispatch_string(t_lexer *lexer, size_t i, t_vec *env);

char	*dispatch_operator(t_lexer *lexer);

static inline t_token	*other_tk(char c, t_lexer *lexer, t_vec *env, size_t i)
{
	t_token	*t;

	t = malloc(sizeof(t_token));
	if ((ft_isspace(c) || !c)
		|| (c == LIT_QUOTE || c == LIT_DOUBLE_QUOTE)
		|| (c == *LIT_REDIR_OUT || c == *LIT_REDIR_IN || c == *LIT_PIPE))
	{
		*t = (t_token){.known_literal = false,
			.s = dispatch_normal(lexer, i, env)};
		return (t);
	}
	free(t);
	return (NULL);
}

static inline t_token	*get_tk(char c, t_lexer *lexer, t_vec *env, size_t i)
{
	t_token	*t;

	t = malloc(sizeof(t_token));
	if (i == 0)
	{
		if (c == *LIT_REDIR_OUT
			|| c == *LIT_REDIR_IN
			|| c == *LIT_PIPE)
		{
			*t = (t_token){.known_literal = false,
				.s = dispatch_operator(lexer)};
			return (t);
		}
		else if (c == LIT_QUOTE || c == LIT_DOUBLE_QUOTE)
		{
			*t = (t_token){.known_literal = true,
				.s = dispatch_string(lexer, i, env)};
			return (t);
		}
	}
	free(t);
	return (other_tk(c, lexer, env, i));
}

#endif
