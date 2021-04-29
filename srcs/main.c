/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-omar <mel-omar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 17:04:42 by mel-omar          #+#    #+#             */
/*   Updated: 2021/04/29 15:55:26 by mel-omar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"
int					arguments[5];
long					time_program_start;
pthread_mutex_t 	*forks;


void	ft_putstr(const char *str)
{
	while (*str)
	{
		write(1, str, sizeof(char));
		str++;
	}
}

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

	position = *((int *)data);
	printf("%ld %d is thinking\n", get_time() - time_program_start, position);
	pthread_mutex_lock(&forks[(position + 1) % arguments[NUMBER_OF_PHILO]]);
	printf("%ld %d has taken a fork\n", get_time() - time_program_start, position);
	pthread_mutex_lock(&forks[position]);
	printf("%ld %d has taken a fork\n", get_time() - time_program_start, position);
	printf("%ld %d is eating\n", get_time() - time_program_start, position);
	usleep(arguments[TIME_TO_EAT]);
	printf("%ld %d is sleeping\n", get_time() - time_program_start, position);
	pthread_mutex_unlock(&forks[position]);
	pthread_mutex_unlock(&forks[(position + 1) % arguments[NUMBER_OF_PHILO]]);
	usleep(arguments[TIME_TO_SLEEP]);
	return (NULL);
}

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000000 + time.tv_usec);
}

void	init_mutexes(pthread_mutex_t *mutexes)
{
	int		iter;

	iter = 0;
	while (iter < arguments[NUMBER_OF_PHILO])
	{
		pthread_mutex_init(&mutexes[iter], NULL);
		iter++;
	}
}

int		main(int argc, char *argv[])
{
	pthread_t	*philosophers;
	int			*philo_id;
	//int			i = 0;
	memset(arguments, 0, sizeof(int) * 5);
	set_arguments(arguments, argc, argv);
	philo_id = malloc(sizeof(int) * arguments[NUMBER_OF_PHILO]);
	forks = malloc(sizeof(pthread_mutex_t) * arguments[NUMBER_OF_PHILO]);
	philosophers = malloc(sizeof(pthread_t) * arguments[NUMBER_OF_PHILO]);
	time_program_start = get_time();
	//printf("NUMBER OF PHILSOPHERS %d\n", arguments[NUMBER_OF_PHILO]);
	//printf("TIME TO EAT %d\n", arguments[TIME_TO_EAT]);
	init_mutexes(forks);
	for (int i = 0; i < arguments[NUMBER_OF_PHILO]; i++)
		philo_id[i] = i;
	//pthread_create(&philosophers[0], NULL, check_function, &philo_id[0]);
	for (int i = 0; i < arguments[NUMBER_OF_PHILO]; i++)
		pthread_create(&philosophers[i], NULL, check_function, &philo_id[i]);
	for (int i = 0; i < arguments[NUMBER_OF_PHILO]; i++)
		pthread_join(philosophers[i], NULL);
	free(forks);
	free(philosophers);
	free(philo_id);
	return (0);
}
