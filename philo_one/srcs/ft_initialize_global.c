/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialize_global.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-omar <mel-omar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 21:09:50 by mel-omar          #+#    #+#             */
/*   Updated: 2021/05/27 14:40:05 by mel-omar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	set_arguments(struct s_global *shared_data, int argc, char *argv[])
{
	int		iterator;

	iterator = 0;
	while (++iterator < argc)
		shared_data->arguments[iterator - 1] = string2number(argv[iterator]);
	shared_data->arguments[TIME_TO_EAT] *= 1000;
	shared_data->arguments[TIME_TO_SLEEP] *= 1000;
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

void	init_global_var(struct s_global *shared_data, int argc, char *argv[])
{
	memset(shared_data->arguments, 0, sizeof(int) * 5);
	set_arguments(shared_data, argc, argv);
	shared_data->forks = malloc(sizeof(pthread_mutex_t)
			* (shared_data->arguments[NUMBER_OF_PHILO]));
	init_forks(shared_data, shared_data->forks);
	pthread_mutex_init(&shared_data->output_manger, NULL);
	shared_data->program_start = get_time();
	shared_data->someone_died = 0;
	shared_data->all_eat = 0;
}
