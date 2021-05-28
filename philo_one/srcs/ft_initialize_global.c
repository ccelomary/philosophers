/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialize_global.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-omar <mel-omar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 21:09:50 by mel-omar          #+#    #+#             */
/*   Updated: 2021/05/28 16:33:15 by mel-omar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"
# include <stdio.h>
int	set_arguments(struct s_global *shared_data, int argc, char *argv[])
{
	int		iterator;

	iterator = 0;
	while (++iterator < argc)
	{
		shared_data->arguments[iterator - 1] = (int)string2number(argv[iterator]);
		if ((shared_data->arguments[iterator - 1]) <= 0)
			return (1);
	}
	shared_data->arguments[TIME_TO_EAT] *= 1000;
	shared_data->arguments[TIME_TO_SLEEP] *= 1000;
	shared_data->arguments[TIME_TO_DIE] *= 1000;
	return (0);
}

void	init_forks(struct s_global *shared_data, pthread_mutex_t *mutexes)
{
	int		iter;

	iter = 0;
	while (iter < shared_data->arguments[NUMBER_OF_PHILO])
	{
		pthread_mutex_init(&mutexes[iter], NULL);
		iter++;
	}
}

int	init_global_var(struct s_global *shared_data, int argc, char *argv[])
{
	memset(shared_data->arguments, 0, sizeof(int) * 5);
	if (set_arguments(shared_data, argc, argv))
		return (1);
	shared_data->forks = malloc(sizeof(pthread_mutex_t)
			* (shared_data->arguments[NUMBER_OF_PHILO]));
	if (!shared_data->forks)
		return (1);
	init_forks(shared_data, shared_data->forks);
	pthread_mutex_init(&shared_data->output_manger, NULL);
	pthread_mutex_init(&shared_data->protect_forks, NULL);
	shared_data->someone_died = 0;
	shared_data->all_eat = 0;
	return (0);
}
