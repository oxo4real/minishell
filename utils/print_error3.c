/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:37:07 by aaghzal           #+#    #+#             */
/*   Updated: 2025/02/22 18:52:16 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	print_error3(char *shell_name, char *command, char *details,
		char *description)
{
	ft_putstr_fd(shell_name, STDERR_FILENO);
	if (shell_name && (command || details || description))
		ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(command, STDERR_FILENO);
	if (command && (details || description))
		ft_putstr_fd(": ", STDERR_FILENO);
	if (details)
	{
		ft_putstr_fd("`", STDERR_FILENO);
		ft_putstr_fd(details, STDERR_FILENO);
		ft_putstr_fd("'", STDERR_FILENO);
	}
	if (details && description)
		ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(description, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}
