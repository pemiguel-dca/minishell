/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:59:12 by pnobre-m          #+#    #+#             */
/*   Updated: 2023/04/20 21:16:34 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "../env_vars/env.h"

t_vec	trim_empty(t_vec tokens)
{
	size_t	i;
	t_vec	new;
	t_token	*el;

	i = 0;
	new = vec_new();
	while (i < tokens.len)
	{
		el = tokens.buf[i];
		if (ft_strlen(el->s) > 0)
			vec_push(&new, el);
		else
		{
			free(el->s);
			free(el);
		}
		i += 1;
	}
	free(tokens.buf);
	return (new);
}

char	*next_var(const char *s)
{
	size_t	i;
	char	*res;

	i = 0;
	res = NULL;
	while (i < ft_strlen(s))
	{
		if (s[i] == '$')
		{
			res = exp_var(s, i);
			if (res)
				return (res);
		}
		i += 1;
	}
	return (NULL);
}

char	*replace_var(const char *s, const char *sub, const char *with)
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

char	*expand_token(const char *token, t_vec *env)
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
		buf = help_expand(buf, env, var);
		free(tmp);
		free(var);
	}
	return (buf);
}

char	*join_next(t_lexer *lexer,
					const char *token,
					t_vec *env,
					bool is_quoted)
{
	char	curr;
	char	*join;
	char	*tmp;

	curr = *l_curr(lexer, 0);
	if (curr && !ft_isspace(curr)
		&& (curr == LIT_QUOTE || curr == LIT_DOUBLE_QUOTE || is_quoted)
	)
	{
		join = get_next(env, lexer)->s;
		tmp = (char *)token;
		token = ft_strjoin(token, join);
		free(tmp);
		free(join);
	}
	return ((char *)token);
}
