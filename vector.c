/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 19:01:35 by pedro             #+#    #+#             */
/*   Updated: 2023/03/20 13:00:19 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "vector.h"
#include <stdio.h>

static void	update_cap(t_vec *vec)
{
	void	*new_buf;

	vec->cap *= 2;
	new_buf = malloc(sizeof(void *) * vec->cap);
	ft_memcpy(new_buf, vec->buf, vec->len * sizeof(void *));
	free(vec->buf);
	vec->buf = new_buf;
}

void	vec_push(t_vec *vec, void *el)
{
	if (vec->len >= vec->cap)
		update_cap(vec);
	vec->buf[vec->len] = el;
	vec->len += 1;
}

void vec_del(t_vec **vec, size_t pos)
{
	t_vec	*v;

	v = *vec;
	if (pos >= v->len)
		return;
	free(v->buf[pos]);
	while (pos < v->len - 1)
	{
		v->buf[pos] = v->buf[pos + 1];
		pos += 1;
	}
	v->len -= 1;
	v->cap /= 2;
}
