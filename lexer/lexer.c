/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 00:30:39 by pedro             #+#    #+#             */
/*   Updated: 2023/04/20 18:01:05 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "lexer.h"

char	*dispatch_operator(t_lexer *lexer)
{
	char	*token;
	size_t	n;

	if (ft_strnstr(lexer->input, LIT_REDIR_DEL, sizeof(LIT_REDIR_DEL) - 1))
		g_signals.is_heredoc = true;
	if (
		ft_strnstr(lexer->input, LIT_REDIR_APPEND, sizeof(LIT_REDIR_APPEND) - 1)
		|| ft_strnstr(lexer->input, LIT_REDIR_DEL, sizeof(LIT_REDIR_DEL) - 1)
	)
		n = sizeof(LIT_REDIR_APPEND) - 1;
	else if (
		ft_strnstr(lexer->input, LIT_PIPE, sizeof(LIT_PIPE) - 1)
		|| ft_strnstr(lexer->input, LIT_REDIR_OUT, sizeof(LIT_REDIR_OUT) - 1)
		|| ft_strnstr(lexer->input, LIT_REDIR_IN, sizeof(LIT_REDIR_IN) - 1)
	)
		n = sizeof(LIT_PIPE) - 1;
	else
	{
		printf("Invalid operator\n");
		exit(EXIT_FAILURE);
	}
	token = ft_substr(lexer->input, 0, n);
	lexer->input += n;
	return (token);
}

char	*dispatch_string(t_lexer *lexer, size_t i, t_vec *env)
{
	char	*token;
	char	delim;
	char	*start;
	char	*end;
	size_t	delta;

	start = l_curr(lexer, i);
	delim = *start;
	end = ft_strchr(start + 1, delim);
	if (!end)
	{
		printf("Unended quote/dquote\n");
		exit(EXIT_FAILURE);
	}
	delta = end - start;
	token = ft_substr(lexer->input, 1, delta - 1);
	lexer->input += delta + 1;
	if (delim == LIT_DOUBLE_QUOTE && !g_signals.is_heredoc)
		return (join_next(lexer, expand_token(token, env), env, true));
	else
	{
		g_signals.is_heredoc = false;
		return (join_next(lexer, token, env, true));
	}
}

char	*dispatch_normal(t_lexer *lexer, size_t i, t_vec *env)
{
	char	*token;

	token = ft_substr(lexer->input, 0, i);
	lexer->input += i;
	if (!g_signals.is_heredoc)
	{
		return (join_next(lexer, expand_token(token, env), env, false));
	}
	else
	{
		g_signals.is_heredoc = false;
		return (join_next(lexer, token, env, false));
	}
}

t_token	*get_next(t_vec *env, t_lexer *lexer)
{
	t_token	*t;
	size_t	i;
	char	c;

	i = 0;
	while (*l_curr(lexer, i) && ft_isspace(*l_curr(lexer, i)))
		++lexer->input;
	while (*lexer->input)
	{
		c = *l_curr(lexer, i);
		t = get_tk(c, lexer, env, i);
		if (t)
			return (t);
		i += 1;
	}
	return (NULL);
}

t_vec	tokenize(t_vec *env, const char *buf)
{
	t_vec	tokens;
	t_lexer	lexer;
	t_token	*token;

	tokens = vec_new();
	lexer = (t_lexer){.input = buf};
	while (true)
	{
		token = get_next(env, &lexer);
		if (token)
			vec_push(&tokens, token);
		else
			break ;
	}
	return (rearrange_tokens(&tokens));
}
