/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnobre-m <pnobre-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 00:30:39 by pedro             #+#    #+#             */
/*   Updated: 2023/04/06 21:18:50 by pnobre-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "lexer.h"
#include "../env_vars/env.h"

static char	*get_next(t_vec *env, t_lexer *lexer);

// TODO: better implementation
static char	*dispatch_operator(t_lexer *lexer)
{
	char	*token;
	size_t	n;

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

	new_len = strlen(s) - strlen(sub) + strlen(with);
	delta = strstr(s, sub) - s;
	buf = malloc(sizeof(char) * (new_len + 1));
	rem = strstr(s, sub) + strlen(sub);

	memcpy(buf, s, delta);
	memcpy(buf + delta, with, strlen(with));
	memcpy(buf + delta + strlen(with), rem, strlen(rem));

	buf[new_len] = 0;
	return buf;
}

static char	*expand_token(const char *token, t_vec *env)
{
	char	*var;
	char	*buf;
	char	*tmp;
	size_t	i;

	buf = (char *)token;
	while (true)
	{
		var = next_var(buf);
		if (!var)
			break ;
		tmp = buf;
		if (pos_env_var(env, var + 1) != -1) {
			buf = replace_var(buf, var, get_var_value(env->buf[pos_env_var(env, var + 1)]));
		} else {
			buf = replace_var(buf, var, " ");
		}
		free(tmp);
		free(var);
	}
	return (buf);
	// " $USER $ $USER " -> " pnobre-m $ pnobre-m "
}

static char	*join_to_next_if_necessary(t_lexer *lexer, const char *token, t_vec *env)
{
	char	*join;
	char	*tmp;

	if (*l_curr(lexer, 0) && !ft_isspace(*l_curr(lexer, 0)))
	{
		join = get_next(env, lexer);
		tmp = (char *)token;
		token = ft_strjoin(token, join);
		free(tmp);
	}
	return ((char *)token);
}

// TODO: better implementation
static char	*dispatch_string(t_lexer *lexer, size_t i, t_vec *env)
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
	return (join_to_next_if_necessary(lexer, expand_token(token, env), env));
}

static char	*dispatch_normal(t_lexer *lexer, size_t i, t_vec *env)
{
	char	*token;

	token = ft_substr(lexer->input, 0, i);
	lexer->input += i;
	// TODO: call expander here
	return (join_to_next_if_necessary(lexer, expand_token(token, env), env));
}

static char	*get_next(t_vec *env, t_lexer *lexer)
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
			return (dispatch_normal(lexer, i, env));
		else if (c == LIT_QUOTE
			|| c == LIT_DOUBLE_QUOTE)
		{
			if (i == 0)
				return (dispatch_string(lexer, i, env));
			else
				return (dispatch_normal(lexer, i, env));
		}
		else if (c == *LIT_REDIR_OUT
			|| c == *LIT_REDIR_IN
			|| c == *LIT_PIPE)
		{
			if (i == 0)
				return (dispatch_operator(lexer));
			else
				return (dispatch_normal(lexer, i, env));
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

	i = 0;
	rearranged = vec_new();
	redirs = vec_new();
	while (i < tokens->len)
	{
		char *t = tokens->buf[i];

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
		{
			vec_push(&rearranged, ft_strdup(t));
		}
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
