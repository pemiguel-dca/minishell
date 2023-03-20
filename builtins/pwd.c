/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnobre-m <pnobre-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 20:24:51 by pemiguel          #+#    #+#             */
/*   Updated: 2023/03/20 18:07:23 by pnobre-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <linux/limits.h>
#include "builtins.h"

int	_pwd(t_expression *expr)
{
	char	cwd[PATH_MAX];

	if (expr->args.len == 1)
	{
		printf("%s\n", getcwd(cwd, PATH_MAX));
	}
	else
	{
		printf("pwd: too many arguments\n");
		return (1);
	}
	return (0);
}
