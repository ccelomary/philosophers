/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-omar <mel-omar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 17:04:42 by mel-omar          #+#    #+#             */
/*   Updated: 2021/04/27 17:28:32 by mel-omar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"
int					arguments[5];
pthread_mutex_t 	*forks;

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
	pthread_t	*philosophers;

	memset(arguments, 0, sizeof(int) * 5);
	set_arguments(arguments, argc, argv);
	forks = malloc(sizeof(pthread_mutex_t) * arguments[NUMBER_OF_PHILO]);
	philosophers = malloc(sizeof(pthread_t) * arguments[NUMBER_OF_PHILO]);	
	free(forks);
	free(philosophers);
	return (0);
}