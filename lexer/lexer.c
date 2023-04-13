/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnobre-m <pnobre-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 00:30:39 by pedro             #+#    #+#             */
/*   Updated: 2023/04/13 17:41:30 by pnobre-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "lexer.h"
#include "../env_vars/env.h"

static char	*get_next(t_vec *env, t_lexer *lexer, bool *is_heredoc);

static char	*dispatch_operator(t_lexer *lexer, bool *is_heredoc)
{
	char	*token;
	size_t	n;

	if (ft_strnstr(lexer->input, LIT_REDIR_DEL, sizeof(LIT_REDIR_DEL) - 1)) {
		*is_heredoc = true;
	}
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

static char	*next_var(const char *s)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < ft_strlen(s))
	{
		if (s[i] == '$')
		{
			j = 0;
			while (s[i + j + 1] && !ft_isspace(s[i + j + 1]) && s[i + j + 1] != '$') {
				j += 1;
			}
			if (j)
				return (ft_substr(s, i, j + 1));
		}
		i += 1;
	}
	return (NULL);
}

static char	*replace_var(const char *s, const char *sub, const char *with)
{
	size_t	new_len;
	size_t	delta;
	char	*buf;
	char	*rem;

	new_len = ft_strlen(s) - ft_strlen(sub) + ft_strlen(with);
	delta = ft_strnstr(s, sub, ft_strlen(s)) - s;
	buf = malloc(sizeof(char) * (new_len + 1));
	rem = ft_strnstr(s, sub, ft_strlen(s)) + ft_strlen(sub);

	ft_memcpy(buf, s, delta);
	ft_memcpy(buf + delta, with, ft_strlen(with));
	ft_memcpy(buf + delta + ft_strlen(with), rem, ft_strlen(rem));

	buf[new_len] = 0;
	return (buf);
}

static char	*expand_token(const char *token, t_vec *env)
{
	char	*var;
	char	*buf;
	char	*tmp;

	buf = (char *)token;
	while (true)
	{
		var = next_var(buf);
		if (!var)
			break ;
		tmp = buf;
		if (is_last_status(buf))
			buf = ft_itoa(g_signals.exit_status);
		else if (pos_env_var(env, var + 1) != -1)
			buf = replace_var(buf, var, get_var_value(env->buf[pos_env_var(env, var + 1)]));
		else
			buf = replace_var(buf, var, "");
		free(tmp);
		free(var);
	}
	return (buf);
}

static char	*join_to_next_if_necessary(t_lexer *lexer, const char *token, t_vec *env, bool *is_heredoc, bool is_quoted)
{
	char	curr;
	char	prev;
	char	*join;
	char	*tmp;

	curr = *l_curr(lexer, 0);
	prev = *(lexer->input - 1);
	if (curr && (curr == LIT_QUOTE || curr == LIT_DOUBLE_QUOTE || is_quoted))
	{
		join = get_next(env, lexer, is_heredoc);
		tmp = (char *)token;
		token = ft_strjoin(token, join);
		free(tmp);
		free(join);
	}
	return ((char *)token);
}

static char	*dispatch_string(t_lexer *lexer, size_t i, t_vec *env, bool *is_heredoc)
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
	if (delim == LIT_DOUBLE_QUOTE && !*is_heredoc)
		return (join_to_next_if_necessary(lexer, expand_token(token, env), env, is_heredoc, true));
	else {
		*is_heredoc = false;
		return (join_to_next_if_necessary(lexer, token, env, is_heredoc, true));
	}
}

static char	*dispatch_normal(t_lexer *lexer, size_t i, t_vec *env, bool *is_heredoc)
{
	char	*token;

	token = ft_substr(lexer->input, 0, i);
	lexer->input += i;
	if (!*is_heredoc) {
		return (join_to_next_if_necessary(lexer, expand_token(token, env), env, is_heredoc, false));
	} else {
		*is_heredoc = false;
		return (join_to_next_if_necessary(lexer, token, env, is_heredoc, false));
	}
}

t_vec	trim_empty(t_vec tokens)
{
	size_t	i;
	t_vec	new;
	char	*el;

	i = 0;
	new = vec_new();
	while (i < tokens.len)
	{
		el = tokens.buf[i];
		if (ft_strlen(el) > 0)
		{
			vec_push(&new, ft_strdup(el));
		}
		i += 1;
	}
	vec_free(&tokens);
	return (new);
}

static char	*get_next(t_vec *env, t_lexer *lexer, bool *is_heredoc)
{
	size_t	i;
	char	c;

	i = 0;
	while (*l_curr(lexer, i) && ft_isspace(*l_curr(lexer, i)))
		++lexer->input;
	while (*lexer->input)
	{
		c = *l_curr(lexer, i);
		if (ft_isspace(c) || !c)
			return (dispatch_normal(lexer, i, env, is_heredoc));
		else if (c == LIT_QUOTE
			|| c == LIT_DOUBLE_QUOTE)
		{
			if (i == 0)
				return (dispatch_string(lexer, i, env, is_heredoc));
			else
				return (dispatch_normal(lexer, i, env, is_heredoc));
		}
		else if (c == *LIT_REDIR_OUT
			|| c == *LIT_REDIR_IN
			|| c == *LIT_PIPE)
		{
			if (i == 0)
				return (dispatch_operator(lexer, is_heredoc));
			else
				return (dispatch_normal(lexer, i, env, is_heredoc));
		}
		i += 1;
	}
	return (NULL);
}

static void	join_channels(t_vec *rearranged, t_vec *redirs)
{
	size_t	i;

	i = 0;
	while (i < redirs->len)
	{
		vec_push(rearranged, ft_strdup(redirs->buf[i]));
		i += 1;
	}
	vec_free(redirs);
	*redirs = vec_new();
}

static t_vec	rearrange_tokens(t_vec *tokens)
{
	size_t	i;
	t_vec	rearranged;
	t_vec	redirs;
	char *t;

	i = 0;
	rearranged = vec_new();
	redirs = vec_new();
	while (i < tokens->len)
	{
		t = tokens->buf[i];
		if (is_redir(t))
		{
			vec_push(&redirs, ft_strdup(t));
			i += 1;
			if (i < tokens->len)
			{
				char *rhs = tokens->buf[i];
				vec_push(&redirs, ft_strdup(rhs));
			}
		}
		else if (ft_strcmp(t, LIT_PIPE) == 0)
		{
			join_channels(&rearranged, &redirs);
			vec_push(&rearranged, ft_strdup(t));
		}
		else
			vec_push(&rearranged, ft_strdup(t));
		i += 1;
	}
	join_channels(&rearranged, &redirs);
	vec_free(&redirs);
	vec_free(tokens);
	return (rearranged);
}

t_vec	tokenize(t_vec *env, const char *buf)
{
	t_vec	tokens;
	t_lexer	lexer;
	char	*token;
	bool	is_heredoc;

	tokens = vec_new();
	lexer = (t_lexer){.input = buf};
	is_heredoc = false;
	while (true)
	{
		token = get_next(env, &lexer, &is_heredoc);
		if (token)
			vec_push(&tokens, token);
		else
			break ;
	}
	return (rearrange_tokens(&tokens));
}
