/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 18:53:07 by pedro             #+#    #+#             */
/*   Updated: 2023/03/19 19:02:46 by pemiguel         ###   ########.fr       */
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
void		vec_push(t_vec *vec, void *el);

/*Initialize a vector*/
inline static t_vec	vec_new(void)
{
	return ((t_vec){
		.len = 0,
		.cap = INIT_CAP,
		.buf = malloc(sizeof(void *) * INIT_CAP)
	});
}

/*Deletes one specific vector member*/
inline static void vec_del(t_vec *vec, size_t pos)
{
	size_t	i;

	i = 0;
	if (pos >= vec->len)
		return;
	free(vec->buf[pos]);
	while (i < vec->len - 1)
	{
		vec->buf[i] = vec->buf[i + 1];
		i += 1;
	}
	vec->len -= 1;
}

/*Free the memory in vector*/
inline static void	vec_free(t_vec *vec)
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
