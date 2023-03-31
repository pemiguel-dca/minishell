/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 22:28:04 by pemiguel          #+#    #+#             */
/*   Updated: 2023/03/31 15:06:02 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	flag_on(t_expression *expr)
{
	if (expr->args.len > 1
		&& ft_strcmp("-n", (char *)expr->args.buf[1]) == 0)
		return (1);
	return (0);
}

static void	free_print(char **echo_print, t_expression *expr)
{
	size_t	i;

	i = 0;
	while (echo_print[i])
	{
		printf("%s", echo_print[i]);
		free(echo_print[i]);
		i += 1;
	}
	free(echo_print);
	if (!flag_on(expr))
		printf("\n");
}

size_t	_echo(t_expression *expr)
{
	size_t	i;
	size_t	j;
	char	**echo_print;
	char	*spaced_args;

	i = 1 + flag_on(expr);
	j = 0;
	echo_print = malloc((expr->args.len - flag_on(expr)) * sizeof(char *));
	while (i < expr->args.len)
	{
		if (i + 1 <= expr->args.len)
		{
			if (i < expr->args.len - 1)
				spaced_args = ft_strjoin(expr->args.buf[i], " ");
			else
				spaced_args = ft_strdup(expr->args.buf[i]);
			echo_print[j] = ft_strdup(spaced_args);
			free(spaced_args);
			j += 1;
		}
		i += 1;
	}
	echo_print[j] = 0;
	free_print(echo_print, expr);
	return (0);
}
