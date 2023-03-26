/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 15:53:22 by pemiguel          #+#    #+#             */
/*   Updated: 2023/03/26 18:02:37 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globals.h"

extern t_signals	g_signals;

void	sig_int(int n)
{
	(void)n;

	if (g_signals.pid == 0)
		g_signals.exit_status = 1;
	else
		g_signals.exit_status = 130;
	printf("\n");
	rl_replace_line("", 0);
	rl_redisplay();
	g_signals.sig_int = true;
}

void	sig_quit(int n)
{
	(void)n;
	printf("CTRL/D");
	if (g_signals.pid == 0)
	{
		printf("exit");
		g_signals.exit_status = 131;
		g_signals.sig_quit = true;
	}
}