/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 20:24:51 by pemiguel          #+#    #+#             */
/*   Updated: 2023/03/20 21:32:20 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	_pwd(t_expression *expr)
{
	char	cwd[PATH_MAX];

	if (expr->args.len == 1)
		printf("%s\n", getcwd(cwd, PATH_MAX));
	else
	{
		printf("pwd: too many arguments\n");
		return (1);
	}
	return (0);
}
