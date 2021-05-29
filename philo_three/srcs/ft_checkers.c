/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-omar <mel-omar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 14:05:12 by mel-omar          #+#    #+#             */
/*   Updated: 2021/05/29 21:39:16 by mel-omar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

long long	difference_ab(long long a, long long b)
{
	return (a - b);
}

void	check_time(t_philosopher *ph, long long t,
	long long duration, int type)
{
	usleep(ph->shared_data->arguments[type] - 20000);
	while ((get_time() - t) < duration)
		;
}

void	check_philosopher(t_philosopher *ph)
{
	while (1)
	{
		if (ph->state != EATING
			&& difference_ab(get_time(), ph->last_time_eat)
			> ph->shared_data->arguments[TIME_TO_DIE])
		{
			death_statement(ph);
			exit(DEAD);
		}
		if (ph->time_eat >= ph->shared_data->arguments[NUMBER_MUST_EAT]
			&& ph->shared_data->arguments[NUMBER_MUST_EAT] != 0)
		{
			pthread_join(ph->thread, NULL);
			exit(DONE);
		}
		usleep(90);
	}
}

void	wait4process(t_philosopher *ph)
{
	int		status;
	int		iter;

	waitpid(-1, &status, 0);
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == DEAD)
		{
			iter = -1;
			while (++iter < ph->shared_data->arguments[NUMBER_OF_PHILO])
				kill(ph[iter].pid, SIGKILL);
		}
	}
}
