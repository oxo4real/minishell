/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unexpected.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:06:16 by mhayyoun          #+#    #+#             */
/*   Updated: 2025/02/25 18:27:29 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	print_unexpected(char *msg)
{
	ft_putstr_fd(SH_NAME ": ", 2);
	ft_putstr_fd(UNEXPECTED_TK " ", 2);
	ft_putchar_fd('`', 2);
	ft_putstr_fd(msg, 2);
	ft_putchar_fd('\'', 2);
	ft_putchar_fd('\n', 2);
}
