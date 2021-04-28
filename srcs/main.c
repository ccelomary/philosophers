/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-omar <mel-omar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 17:04:42 by mel-omar          #+#    #+#             */
/*   Updated: 2021/04/28 01:06:58 by mel-omar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"
int					arguments[5];
int					*forks_locked;
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

void	*check_function(void *data)
{
	int		position;

	position = *(int *)data;
	printf("PHILO %d thinking\n", position + 1);
	if (!forks_locked[position])
	{
		forks_locked[position] = 1;
		forks_locked[(position + 1) % arguments[NUMBER_OF_PHILO]] = 1;
		pthread_mutex_lock(&forks[position]);
		pthread_mutex_lock(&forks[(position + 1) % arguments[NUMBER_OF_PHILO]]);
	}
	printf("PHILO %d eats\n", position + 1);
	usleep(600000);
	pthread_mutex_unlock(&forks[position]);
	pthread_mutex_unlock(&forks[(position + 1) % arguments[NUMBER_OF_PHILO]]);
	forks_locked[position] = 0;
	forks_locked[(position + 1) % arguments[NUMBER_OF_PHILO]] = 0;
	printf("PHILP %d sleep\n", position + 1);
	usleep(15);
	return (NULL);
}
int		main(int argc, char *argv[])
{
	pthread_t	*philosophers;
	//int			i = 0;
	memset(arguments, 0, sizeof(int) * 5);
	set_arguments(arguments, argc, argv);
	forks = malloc(sizeof(pthread_mutex_t) * arguments[NUMBER_OF_PHILO]);
	forks_locked = malloc(sizeof(int) * arguments[NUMBER_OF_PHILO]);
	memset(forks_locked, 0, sizeof(int) * arguments[NUMBER_OF_PHILO]);
	philosophers = malloc(sizeof(pthread_t) * arguments[NUMBER_OF_PHILO]);
	printf("NUMBER OF PHILSOPHERS %d\n", arguments[NUMBER_OF_PHILO]);
	for (int i = 0; i < arguments[NUMBER_OF_PHILO]; i++)
	{
		pthread_create(&philosophers[i], NULL, check_function, &i);
		pthread_join(philosophers[i], NULL);
	}
	free(forks);
	free(philosophers);
	free(forks_locked);
	return (0);
}
