/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialize_global.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-omar <mel-omar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 21:09:50 by mel-omar          #+#    #+#             */
/*   Updated: 2021/05/01 17:34:48 by mel-omar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	set_arguments(int argc, char *argv[])
{
	int		iterator;

	iterator = 0;
	while (++iterator < argc)
		g_global_var.arguments[iterator - 1] = string2number(argv[iterator]);
	g_global_var.arguments[TIME_TO_DIE] *= 1000;
	g_global_var.arguments[TIME_TO_EAT] *= 1000;
	g_global_var.arguments[TIME_TO_SLEEP] *= 1000;
	
}

void	init_forks(pthread_mutex_t *mutexes)
{
	int		iter;

	iter = 0;
	while (iter < g_global_var.arguments[NUMBER_OF_PHILO])
	{
		pthread_mutex_init(&mutexes[iter], NULL);
		iter++;
	}
}

void			init_global_var(int argc, char *argv[])
{
	int		iterator;

	memset(g_global_var.arguments, 0, sizeof(int) * 5);
	set_arguments(argc, argv);
	g_global_var.forks = malloc(sizeof(pthread_mutex_t) * (g_global_var.arguments[NUMBER_OF_PHILO]));
	init_forks(g_global_var.forks);
	pthread_mutex_init(&g_global_var.output_manger, NULL);
	g_global_var.program_start = get_time();
	g_global_var.someone_died = 0;
	g_global_var.all_eat = 0;
}