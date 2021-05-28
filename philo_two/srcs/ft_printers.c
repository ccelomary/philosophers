/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-omar <mel-omar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 21:35:35 by mel-omar          #+#    #+#             */
/*   Updated: 2021/05/27 16:49:51 by mel-omar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	ft_putc(char c)
{
	write(1, &c, sizeof(char));
}

void	endl(void)
{
	ft_putc('\n');
}

void	ft_putnbr(unsigned int number)
{
	if (number / 10)
		ft_putnbr(number / 10);
	ft_putc((number % 10) + 48);
}

void	ft_putstr(const char *str)
{
	while (*str)
	{
		ft_putc(*str);
		str++;
	}
}

void	ft_print_error(const char *s)
{
	while (*s)
	{
		write (2, s, 1);
		s++;
	}
}
