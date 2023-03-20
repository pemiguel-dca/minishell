/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 19:01:35 by pedro             #+#    #+#             */
/*   Updated: 2023/03/19 22:21:32 by pemiguel         ###   ########.fr       */
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
	size_t	i;
	t_vec	*v;

	i = 0;
	v = *vec;
	if (pos >= v->len)
		return;
	free(v->buf[pos]);
	while (i < v->len)
	{
		if (i == pos)
			v->buf[i] = v->buf[i + 1];
		i += 1;
	}
	v->len -= 1;
}
