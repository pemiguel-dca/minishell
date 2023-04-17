/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_rearrange.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnobre-m <pnobre-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 18:40:58 by pnobre-m          #+#    #+#             */
/*   Updated: 2023/04/17 18:48:00 by pnobre-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

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

static void	process_token(size_t *i,
							t_vec *tokens,
							t_vec *rearranged,
							t_vec *redirs)
{
	char	*t;
	char	*rhs;

	t = tokens->buf[*i];
	if (is_redir(t))
	{
		vec_push(redirs, ft_strdup(t));
		i += 1;
		if (*i < tokens->len)
		{
			rhs = tokens->buf[*i];
			vec_push(redirs, ft_strdup(rhs));
		}
	}
	else if (ft_strcmp(t, LIT_PIPE) == 0)
	{
		join_channels(rearranged, redirs);
		vec_push(rearranged, ft_strdup(t));
	}
	else
		vec_push(rearranged, ft_strdup(t));
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
	vec_free(&redirs);
	vec_free(tokens);
	return (rearranged);
}
