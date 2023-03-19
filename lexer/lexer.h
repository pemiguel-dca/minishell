/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 22:28:38 by pedro             #+#    #+#             */
/*   Updated: 2023/03/19 02:34:37 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../vector.h"

typedef struct lexer
{
	const char	*input;
}	t_lexer;

inline static char	*curr(const t_lexer *lexer, size_t i)
{
	return ((char *)lexer->input + i);
}

t_vec	tokenize(const char *buf);

#endif
