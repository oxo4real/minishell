/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:50:45 by mhayyoun          #+#    #+#             */
/*   Updated: 2025/02/27 11:11:39 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing_bonus.h"

void	interrupt(int sig)
{
	(void)sig;
	if (g_sig)
	{
		if (g_sig != 130)
			g_sig = 130;
		return ;
	}
	write(STDERR_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	interrupt_herdoc(int sig)
{
	(void)sig;
	exit(g_sig);
}

void	quit(int sig)
{
	(void)sig;
	if (g_sig)
	{
		if (g_sig != 130)
			g_sig = 130;
		return ;
	}
}
