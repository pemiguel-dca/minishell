/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 22:28:38 by pedro             #+#    #+#             */
/*   Updated: 2023/03/23 13:28:33 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdbool.h>
# include "../globals.h"
# include "../vector.h"
# include "../libft/libft.h"

typedef struct lexer
{
	const char	*input;
}	t_lexer;

inline static char	*curr(const t_lexer *lexer, size_t i)
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

t_vec	tokenize(const char *buf);

#endif
