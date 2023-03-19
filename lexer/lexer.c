/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 00:30:39 by pedro             #+#    #+#             */
/*   Updated: 2023/03/19 02:31:37 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdbool.h>
#include "lexer.h"
#include "../libft/libft.h"
#include "../globals.h"

static char	*get_next(t_lexer *lexer);

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

// TODO: better implementation
static char	*dispatch_string(t_lexer *lexer, size_t i)
{
	char	*token;
	char	delim;
	char	*start;
	char	*end;
	char	*join;
	char	*tmp;
	size_t	delta;

	start = curr(lexer, i);
	delim = *start;
	end = ft_strchr(curr(lexer, i) + 1, delim);
	if (!end)
	{
		printf("Unended quote/dquote\n");
		exit(EXIT_FAILURE);
	}
	delta = end - start;
	token = ft_substr(lexer->input, 1, delta - 1);
	lexer->input += delta + 1;
	if (*curr(lexer, 0) && !ft_isspace(*curr(lexer, 0)))
	{
		join = get_next(lexer);
		tmp = token;
		token = ft_strjoin(token, join);
		free(tmp);
	}
	return (token);
}

static char	*dispatch_normal(t_lexer *lexer, size_t i)
{
	char	*token;

	token = ft_substr(lexer->input, 0, i);
	lexer->input += i;
	return (token);
}

static char	*get_next(t_lexer *lexer)
{
	size_t	i;

	i = 0;
	while (*curr(lexer, i) && ft_isspace(*curr(lexer, i)))
		++lexer->input;
	while (*lexer->input)
	{
		if (ft_isspace(*curr(lexer, i)) || !*curr(lexer, i))
			return (dispatch_normal(lexer, i));
		else if (*curr(lexer, i) == LIT_QUOTE
			|| *curr(lexer, i) == LIT_DOUBLE_QUOTE)
			return (dispatch_string(lexer, i));
		else if (*curr(lexer, i) == *LIT_REDIR_OUT
			|| *curr(lexer, i) == *LIT_REDIR_IN
			|| *curr(lexer, i) == *LIT_PIPE)
		{
			if (i == 0)
				return (dispatch_operator(lexer));
			else
				return (dispatch_normal(lexer, i));
		}
		++i;
	}
	return (NULL);
}

t_vec	tokenize(const char *buf)
{
	t_vec	tokens;
	t_lexer	lexer;
	char	*token;

	tokens = vec_new();
	lexer = (t_lexer){.input = buf};
	while (true)
	{
		token = get_next(&lexer);
		if (token)
			vec_push(&tokens, token);
		else
			break ;
	}
	return (tokens);
}
