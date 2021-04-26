/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-omar <mel-omar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 17:04:42 by mel-omar          #+#    #+#             */
/*   Updated: 2021/04/26 17:18:17 by mel-omar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	set_arguments(int *arguments, int argc, char *argv[])
{
	int		iterator;

	iterator = 1;
	while (iterator  < argc)
	{
		arguments[iterator - 1] = string2number(argv[iterator]);
		iterator++;
	}
}

int		main(int argc, char *argv[])
{
	int			arguments[5];

	memset(arguments, 0, sizeof(int) * 5);
	set_arguments(arguments, argc, argv);
	printf("NUMBER OF PHILOSOPHERS %d\n", arguments[NUMBER_OF_PHILO]);
	printf("TIME TO EAT %d\n", arguments[TIME_TO_EAT]);
	printf("TIME TO DIE %d\n", arguments[TIME_TO_DIE]);
	printf("TIME TO SLEEP %d\n", arguments[TIME_TO_SLEEP]);
	printf("NUMBER OF TIME EACH PHILOSOPHER MUST EAT %d\n", arguments[NUMBER_MUST_EAT]);
	return (0);
}