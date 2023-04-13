/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnobre-m <pnobre-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 15:53:22 by pemiguel          #+#    #+#             */
/*   Updated: 2023/04/13 18:12:12 by pnobre-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globals.h"

extern t_signals	g_signals;

void	sig_int(int n)
{
	(void)n;
	g_signals.exit_status = 130;
	if (!g_signals.is_in_child) {
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	} else {
		g_signals.is_in_child = false;
		exit(g_signals.exit_status);
	}
}
