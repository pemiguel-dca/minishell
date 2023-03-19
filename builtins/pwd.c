/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 20:24:51 by pemiguel          #+#    #+#             */
/*   Updated: 2023/03/19 16:39:22 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	_pwd(t_expression *expr)
{
	char	*buf = NULL;

	if (expr->args.len == 1)
		printf("%s\n", getcwd(buf, 0));
	else
		printf("pwd: too many arguments\n");
	exit (EXIT_SUCCESS);
}

