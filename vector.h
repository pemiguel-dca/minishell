/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 18:53:07 by pedro             #+#    #+#             */
/*   Updated: 2023/03/18 20:10:44 by pemiguel         ###   ########.fr       */
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

/*Update capacity of the vector*/
static void	update_cap(t_vec *vec);
/*Push content to a vector*/
void  vec_push(t_vec *vec, void *el);

/*Initialize a vector*/
inline static t_vec	vec_new()
{
	return ((t_vec){
		.len = 0,
		.cap = INIT_CAP,
		.buf = malloc(sizeof(void *) * INIT_CAP)
	});
}
/*Free the memory in vector*/
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
