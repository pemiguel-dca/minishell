/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnobre-m <pnobre-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 16:25:06 by pnobre-m          #+#    #+#             */
/*   Updated: 2022/11/12 17:12:15 by pnobre-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;
	t_list	*i;

	if (!lst || !del)
		return ;
	tmp = *lst;
	while (tmp)
	{
		i = tmp->next;
		ft_lstdelone(tmp, del);
		tmp = i;
	}
	*lst = NULL;
}
