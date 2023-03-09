/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 19:01:35 by pedro             #+#    #+#             */
/*   Updated: 2023/03/07 20:06:14 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "vector.h"

static void	update_cap(t_vec *vec)
{
	void	*new_buf;

	vec->cap *= 2;
	new_buf = malloc(sizeof(void *) * vec->cap);
	ft_memcpy(new_buf, vec->buf, vec->len * sizeof(void *));
	free(vec->buf);
	vec->buf = new_buf;
}

void  vec_push(t_vec *vec, void *el)
{
	if (vec->len >= vec->cap)
	{
		update_cap(vec);
	}

	vec->buf[vec->len] = el;
	vec->len += 1;
}
