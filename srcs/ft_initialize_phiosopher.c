/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialize_phiosopher.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-omar <mel-omar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 21:23:26 by mel-omar          #+#    #+#             */
/*   Updated: 2021/05/03 16:33:57 by mel-omar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void		init_philosopher(t_philosopher *philo, int id)
{
	philo->id = id;
	philo->time_eat = 0;
	philo->last_time_eat = g_global_var.program_start;
	philo->state = THINKING;
	pthread_mutex_init(&philo->is_eating, NULL);
}

t_philosopher *init_philosophers(void)
{
	t_philosopher	*philosophers;
	int				iterator;

	philosophers = malloc(sizeof(t_philosopher) * g_global_var.arguments[NUMBER_OF_PHILO]);
	iterator = 0;
	while (iterator < g_global_var.arguments[NUMBER_OF_PHILO])
	{
		init_philosopher(&philosophers[iterator], iterator);
		iterator++;
	}
	return (philosophers);
}
