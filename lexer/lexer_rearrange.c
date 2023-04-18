/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_rearrange.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnobre-m <pnobre-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 18:40:58 by pnobre-m          #+#    #+#             */
/*   Updated: 2023/04/18 18:19:59 by pnobre-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

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
