/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-omar <mel-omar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 17:04:42 by mel-omar          #+#    #+#             */
/*   Updated: 2021/04/30 01:33:52 by mel-omar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"


int		count_finished_philosophers(t_philosopher *ph)
{
	int		iter;
	int		counter;

	iter = 0;
	counter = 0;
	while (iter < g_global_var.arguments[NUMBER_OF_PHILO])
	{
		if (ph[iter].time_eat >= g_global_var.arguments[NUMBER_MUST_EAT])
			counter++;
		iter++;
	}
	return (counter);
}

int		check_someone_died(t_philosopher *ph)
{
	int		iter;
	int		now;
	iter = 0;
	while (iter < g_global_var.arguments[NUMBER_OF_PHILO])
	{
		now = get_time() - ph[iter].last_time_eat;
		if (ph[iter].state != EATING 
		&& (g_global_var.arguments[TIME_TO_DIE] / 1000) <= now)
		{
			death_statement(&ph[iter]);
			return (1);
		}
		iter++;
	}
	return (0);
}

void	checker_state(t_philosopher *ph)
{
	while (1)
	{
		if (check_someone_died(ph))
		{
			g_global_var.someone_died = 1;
			break ;
		}
		if (count_finished_philosophers(ph))
			break ;
	}
}

void	*philosopher_function(void *philo)
{
	t_philosopher	*ph;

	ph = philo;
	while (ph->time_eat < g_global_var.arguments[NUMBER_MUST_EAT]
	&& !g_global_var.someone_died)
	{
		think_statement(ph);
		ph->state = THINKING;
		pthread_mutex_lock(&g_global_var.forks[ph->id]);
		fork_statement(ph);
		pthread_mutex_lock(&g_global_var.forks[(ph->id + 1)
			% g_global_var.arguments[NUMBER_OF_PHILO]]);
		fork_statement(ph);
		eat_statement(ph);
		ph->state = EATING;
		ph->time_eat++;
		usleep(g_global_var.arguments[TIME_TO_EAT]);
		ph->last_time_eat = get_time();
		sleep_statement(ph);
		ph->state = SLEEPING;
		pthread_mutex_unlock(&g_global_var.forks[ph->id]);
		pthread_mutex_unlock(&g_global_var.forks[(ph->id + 1) % g_global_var.arguments[NUMBER_OF_PHILO]]);
		usleep(g_global_var.arguments[TIME_TO_SLEEP]);
	}
	return (NULL);
}

void	run_philosophers(t_philosopher *ph)
{
	int 	iter;

	iter = 0;
	while (iter < g_global_var.arguments[NUMBER_OF_PHILO])
	{
		pthread_create(&ph[iter].thread, NULL, philosopher_function, &ph[iter]);
		iter++;
	}
}

void	wait4philosophers(t_philosopher *ph)
{
		int 	iter;

	iter = 0;
	while (iter < g_global_var.arguments[NUMBER_OF_PHILO])
	{
		pthread_join(ph[iter].thread, NULL);
		iter++;
	}	
}
int		main(int argc, char *argv[])
{
	t_philosopher	*ph;
	int				*philo_id;

	init_global_var(argc, argv);
	ph = init_philosophers();
	run_philosophers(ph);
	checker_state(ph);
	if (g_global_var.someone_died)
		pthread_mutex_unlock(&g_global_var.output_manger);
	else
		wait4philosophers(ph);
	free(g_global_var.forks);
	free(ph);
	return (0);
}
