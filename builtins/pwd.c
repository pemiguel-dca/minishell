/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnobre-m <pnobre-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 20:24:51 by pemiguel          #+#    #+#             */
/*   Updated: 2023/03/02 16:54:20 by pnobre-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	_pwd(t_parser *parser)
{
	char	*buf = NULL;

	if (ft_arraystrlen(parser->args) == 1)
		printf("%s\n", getcwd(buf, 0));
	else
		printf("pwd: too many arguments\n");
	return (0);
}
