/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child_thread.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-omar <mel-omar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 14:13:13 by mel-omar          #+#    #+#             */
/*   Updated: 2021/05/28 18:25:10 by mel-omar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	eating_operation(t_philosopher *ph, long long eat_time)
{
	ph->state = EATING;
	eat_statement(ph);
	ph->time_eat++;
	ph->last_time_eat = get_time();
	check_time(ph, ph->last_time_eat, eat_time, TIME_TO_EAT);
}

int	min(int index1, int index2)
{
	if (index1 > index2)
		return (index2);
	return (index1);
}

int	max(int index1, int index2)
{
	if (index1 > index2)
		return (index1);
	return (index2);
}

static void	init_variables(t_philosopher *ph,
	int minmax[2], long long ueat_sleep[2])
{
	minmax[0] = min(ph->id, (ph->id + 1)
			% ph->shared_data->arguments[NUMBER_OF_PHILO]);
	minmax[1] = max(ph->id, (ph->id + 1)
			% ph->shared_data->arguments[NUMBER_OF_PHILO]);
	ueat_sleep[0] = ph->shared_data->arguments[TIME_TO_EAT];
	ueat_sleep[1] = ph->shared_data->arguments[TIME_TO_SLEEP];
	//pthread_mutex_lock(&ph->shared_data->protect_forks);
}

void	*philosopher_function(void *philo)
{
	t_philosopher	*ph;
	int				minmax[2];
	long long		ueat_sleep[2];

	ph = philo;
	init_variables(ph, minmax, ueat_sleep);
	while ((ph->time_eat < ph->shared_data->arguments[NUMBER_MUST_EAT]
			|| !ph->shared_data->arguments[NUMBER_MUST_EAT])
		&& !ph->shared_data->someone_died)
	{
		ph->state = THINKING;
		think_statement(ph);
		pthread_mutex_lock(&ph->shared_data->forks[ph->id]);
		fork_statement(ph);
		pthread_mutex_lock(&ph->shared_data->forks[(ph->id + 1) % ph->shared_data->arguments[NUMBER_OF_PHILO]]);
		//pthread_mutex_unlock(&ph->shared_data->protect_forks);
		fork_statement(ph);
		eating_operation(ph, ueat_sleep[0]);
		sleep_statement(ph);
		pthread_mutex_unlock(&ph->shared_data->forks[(ph->id + 1) % ph->shared_data->arguments[NUMBER_OF_PHILO]]);
		pthread_mutex_unlock(&ph->shared_data->forks[ph->id]);
		ph->state = SLEEPING;
		check_time(ph, get_time(), ueat_sleep[1], TIME_TO_SLEEP);
	}
	//pthread_mutex_unlock(&ph->shared_data->protect_forks);
	return (NULL);
}
/*
			//1 -> 0, 1
			2 -> 1, 2
			3, -> 2, 3 > 0
*/