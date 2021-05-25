/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child_thread.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-omar <mel-omar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 14:13:13 by mel-omar          #+#    #+#             */
/*   Updated: 2021/05/25 21:14:15 by mel-omar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void eating_operation(t_philosopher *ph)
{
    ph->state = EATING;
    eat_statement(ph);
    ph->time_eat++;
	ph->last_time_eat = get_time();
    check_time(ph, get_time(), ph->shared_data->arguments[TIME_TO_EAT] / 1000, TIME_TO_EAT);
}

int		min(int index1, int index2)
{
	if (index1 > index2)
		return (index2);
	return (index1);
}

int		max(int index1, int index2)
{
	if (index1 > index2)
		return (index1);
	return (index2);
}

void	*philosopher_function(void *philo)
{
	t_philosopher	*ph;

	ph = philo;
	while ((ph->time_eat < ph->shared_data->arguments[NUMBER_MUST_EAT]
		|| !ph->shared_data->arguments[NUMBER_MUST_EAT])
		&& !ph->shared_data->someone_died)
	{
		ph->state = THINKING;
		think_statement(ph);
		pthread_mutex_lock(&ph->shared_data->forks[min(ph->id, (ph->id + 1) % ph->shared_data->arguments[NUMBER_OF_PHILO])]);
		fork_statement(ph);
		pthread_mutex_lock(&ph->shared_data->forks[max(ph->id, (ph->id + 1) % ph->shared_data->arguments[NUMBER_OF_PHILO])]);
		fork_statement(ph);
        eating_operation(ph);
		pthread_mutex_unlock(&ph->shared_data->forks[max(ph->id, (ph->id + 1) % ph->shared_data->arguments[NUMBER_OF_PHILO])]);
		pthread_mutex_unlock(&ph->shared_data->forks[min(ph->id, (ph->id + 1) % ph->shared_data->arguments[NUMBER_OF_PHILO])]);
		ph->state = SLEEPING;
		sleep_statement(ph);
		check_time(ph, get_time(), ph->shared_data->arguments[TIME_TO_SLEEP] / 1000, TIME_TO_SLEEP);
	}
	return (NULL);
}