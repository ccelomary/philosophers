/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child_thread.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-omar <mel-omar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 14:13:13 by mel-omar          #+#    #+#             */
/*   Updated: 2021/05/26 16:30:14 by mel-omar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void eating_operation(t_philosopher *ph, long long eat_time)
{
    ph->state = EATING;
    eat_statement(ph);
    ph->time_eat++;
	ph->last_time_eat = get_time();
    check_time(ph, get_time(), eat_time, TIME_TO_EAT);
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
	long long		ueat, uslp;

	ph = philo;
	sem_wait(ph->shared_data->protect_forks);
	ueat = ph->shared_data->arguments[TIME_TO_EAT];
	uslp = ph->shared_data->arguments[TIME_TO_SLEEP];
	while ((ph->time_eat < ph->shared_data->arguments[NUMBER_MUST_EAT]
		|| !ph->shared_data->arguments[NUMBER_MUST_EAT])
		&& !ph->shared_data->someone_died)
	{
		ph->state = THINKING;
		think_statement(ph);
		sem_wait(ph->shared_data->forks);
		fork_statement(ph);
		sem_wait(ph->shared_data->forks);
		fork_statement(ph);
		sem_post(ph->shared_data->protect_forks);
        eating_operation(ph, ueat);
		sem_post(ph->shared_data->forks);
		sem_post(ph->shared_data->forks);
		ph->state = SLEEPING;
		sleep_statement(ph);
		check_time(ph, get_time(), uslp, TIME_TO_SLEEP);
	}
	return (NULL);
}