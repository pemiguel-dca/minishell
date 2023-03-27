/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnobre-m <pnobre-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 12:56:41 by pemiguel          #+#    #+#             */
/*   Updated: 2023/03/27 16:49:53 by pnobre-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int		digits_in(char *arg)
{
	size_t	i;

	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (1);
		i += 1;
	}
	return (0);
}

void	mini_exit(t_expression *expr, t_executer *params)
{
	size_t	i;

	i = 0;
	params->exit = 1;
	printf("exit\n");
	if (expr->args.len == 1)
		g_signals.exit_status = 0;
	else
	{
		if (expr->args.len > 2)
		{
			printf("exit: too many arguments\n");
			g_signals.exit_status = 1;
			params->exit = 0;
		}
		else
		{
			if (digits_in((char *)expr->args.buf[1]))
				printf("%s: numeric argument required\n", (char *)expr->args.buf[1]);
			else
				g_signals.exit_status = ft_atoi((char *)expr->args.buf[1]);
		}
	}
	return ;
}
