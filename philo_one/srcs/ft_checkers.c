/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-omar <mel-omar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 14:05:12 by mel-omar          #+#    #+#             */
/*   Updated: 2021/05/27 14:28:06 by mel-omar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static long long	difference_ab(long long a, long long b)
{
	return (a - b);
}

static int	count_finished_philosophers(t_philosopher *ph)
{
	int		iter;
	int		counter;

	iter = 0;
	counter = 0;
	while (iter < ph->shared_data->arguments[NUMBER_OF_PHILO])
	{
		if (ph[iter].time_eat >= ph->shared_data->arguments[NUMBER_MUST_EAT]
			&& ph->shared_data->arguments[NUMBER_MUST_EAT])
			counter++;
		iter++;
	}
	return (counter);
}

static int	check_someone_died(t_philosopher *ph)
{
	int		iter;

	iter = -1;
	while (++iter < ph->shared_data->arguments[NUMBER_OF_PHILO])
	{
		if (ph[iter].state != EATING
			&& difference_ab(get_time(),
				ph[iter].last_time_eat)
			> ph->shared_data->arguments[TIME_TO_DIE])
		{
			death_statement(&ph[iter]);
			return (1);
		}
	}
	return (0);
}

void	checker_state(t_philosopher *ph)
{
	while (1)
	{
		if (check_someone_died(ph))
		{
			ph->shared_data->someone_died = 1;
			break ;
		}
		if (count_finished_philosophers(ph))
			break ;
		usleep(1000);
	}
}

void	check_time(t_philosopher *ph, long long t, long long duration, int type)
{
	usleep(ph->shared_data->arguments[type] - 30000);
	while ((get_time() - t) * 1000 < duration)
		;
}
