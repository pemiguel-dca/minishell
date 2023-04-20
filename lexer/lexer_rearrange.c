/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_rearrange.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 18:40:58 by pnobre-m          #+#    #+#             */
/*   Updated: 2023/04/20 21:18:12 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	*help_expand(char *buf, t_vec *env, char *var)
{
	char	*l_status;
	char	*var_value;

	if (is_last_status(buf))
	{
		l_status = ft_itoa(g_signals.exit_status);
		buf = replace_var(buf, var, l_status);
		free(l_status);
	}
	else if (pos_env_var(env, var + 1) != -1)
	{
		var_value = get_var_value(env->buf[pos_env_var(env, var + 1)]);
		buf = replace_var(buf, var, var_value);
	}
	else
		buf = replace_var(buf, var, "");
	return (buf);
}

char	*exp_var(const char *s, size_t i)
{
	size_t	j;

	if (s[i + 1] && s[i + 1] == '?')
		return (ft_substr(s, i, 2));
	else
	{
		j = 0;
		while (s[i + j + 1] && !ft_isspace(s[i + j + 1])
			&& s[i + j + 1] != '$'
			&& s[i + j + 1] != *LIT_REDIR_OUT
			&& s[i + j + 1] != *LIT_REDIR_IN
			&& s[i + j + 1] != *LIT_PIPE
			&& s[i + j + 1] != LIT_QUOTE
			&& s[i + j + 1] != LIT_DOUBLE_QUOTE)
			j += 1;
		if (j)
			return (ft_substr(s, i, j + 1));
	}
	return (NULL);
}

static void	join_channels(t_vec *rearranged, t_vec *redirs)
{
	size_t	i;

	i = 0;
	while (i < redirs->len)
	{
		vec_push(rearranged, redirs->buf[i]);
		i += 1;
	}
	free(redirs->buf);
}

static void	process_token(size_t *i,
							t_vec *tokens,
							t_vec *rearranged,
							t_vec *redirs)
{
	t_token	*t;
	t_token	*rhs;

	t = tokens->buf[*i];
	if (is_redir(t->s) && !t->known_literal)
	{
		vec_push(redirs, t);
		*i += 1;
		if (*i < tokens->len)
		{
			rhs = tokens->buf[*i];
			vec_push(redirs, rhs);
		}
	}
	else if (ft_strcmp(t->s, LIT_PIPE) == 0 && !t->known_literal)
	{
		join_channels(rearranged, redirs);
		*redirs = vec_new();
		vec_push(rearranged, t);
	}
	else
		vec_push(rearranged, t);
}

t_vec	rearrange_tokens(t_vec *tokens)
{
	size_t	i;
	t_vec	rearranged;
	t_vec	redirs;

	i = 0;
	rearranged = vec_new();
	redirs = vec_new();
	while (i < tokens->len)
	{
		process_token(&i, tokens, &rearranged, &redirs);
		i += 1;
	}
	join_channels(&rearranged, &redirs);
	free(tokens->buf);
	return (rearranged);
}
