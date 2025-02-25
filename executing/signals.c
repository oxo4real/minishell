/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:50:45 by mhayyoun          #+#    #+#             */
/*   Updated: 2025/02/25 20:33:39 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

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
