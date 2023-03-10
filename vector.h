/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 18:53:07 by pedro             #+#    #+#             */
/*   Updated: 2023/03/10 16:16:32 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <stdlib.h>

# define INIT_CAP 4

typedef struct vec {
	size_t	len;
	size_t	cap;
	void	**buf;
}	t_vec;

static void	update_cap(t_vec *vec);

void  vec_push(t_vec *vec, void *el);

inline static t_vec	vec_new()
{
	return ((t_vec){
		.len = 0,
		.cap = INIT_CAP,
		.buf = malloc(sizeof(void *) * INIT_CAP)
	});
}

inline static void vec_free(t_vec *vec)
{
	size_t	i;

	i = 0;
	while (i < vec->len)
	{
		free(vec->buf[i]);
		i += 1;
	}
	free(vec->buf);
}

#endif
