/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_checker.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-omar <mel-omar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 14:22:02 by mel-omar          #+#    #+#             */
/*   Updated: 2021/05/27 14:39:11 by mel-omar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	check4errors(int argc, char **argv)
{
	int		iterator;
	int		nested_iter;

	if (argc < 5 || argc > 6)
		return (1);
	iterator = 1;
	while (iterator < argc)
	{
		nested_iter = 0;
		while (argv[iterator][nested_iter])
		{
			if (!isdigits(argv[iterator][nested_iter]))
				return (1);
			nested_iter++;
		}
		iterator++;
	}
	return (0);
}
