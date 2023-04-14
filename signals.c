/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 15:53:22 by pemiguel          #+#    #+#             */
/*   Updated: 2023/04/14 17:15:27 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globals.h"

extern t_signals	g_signals;

void	sig_int(int n)
{
	(void)n;
	g_signals.exit_status = 130;
	if (g_signals.pid == 14)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
		g_signals.pressed_in_child = true;
}

void	ignore_signal(int n)
{
	(void)n;
	g_signals.exit_status = 130;
	exit(g_signals.exit_status);
}
