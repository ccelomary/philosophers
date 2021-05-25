/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-omar <mel-omar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 17:04:42 by mel-omar          #+#    #+#             */
/*   Updated: 2021/05/25 13:17:06 by mel-omar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

long long 	difference_ab(long long a, long long b)
{
	return (a - b);
}

int		count_finished_philosophers(t_philosopher *ph)
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

int		check_someone_died(t_philosopher *ph)
{
	int		iter;
	
	iter = -1;
	while (++iter < ph->shared_data->arguments[NUMBER_OF_PHILO])
	{
		if (difference_ab(get_time(), ph[iter].last_time_eat) > ph->shared_data->arguments[TIME_TO_DIE]
			&& ph[iter].state != EATING)
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
	}
}

void	check_time(t_philosopher *ph, long long t, long long duration, int type)
{
	usleep(ph->shared_data->arguments[type] - 30000);
	while ((get_time() - t) < duration);
}
void	*philosopher_function(void *philo)
{
	t_philosopher	*ph;

	ph = philo;
	pthread_mutex_lock(&ph->shared_data->protect_forks);
	while ((ph->time_eat < ph->shared_data->arguments[NUMBER_MUST_EAT]
		|| !ph->shared_data->arguments[NUMBER_MUST_EAT])
		&& !ph->shared_data->someone_died)
	{
		ph->state = THINKING;
		think_statement(ph);
		pthread_mutex_unlock(&ph->shared_data->protect_forks);
		pthread_mutex_lock(&ph->shared_data->forks[ph->id]);
		fork_statement(ph);
		pthread_mutex_lock(&ph->shared_data->forks[(ph->id + 1)
			% ph->shared_data->arguments[NUMBER_OF_PHILO]]);
		fork_statement(ph);
		ph->state = EATING;
		eat_statement(ph);
		ph->time_eat++;
		ph->last_time_eat = get_time();
		check_time(ph, get_time(), ph->shared_data->arguments[TIME_TO_EAT] / 1000, TIME_TO_EAT);
		pthread_mutex_unlock(&ph->shared_data->forks[ph->id]);
		pthread_mutex_unlock(&ph->shared_data->forks[(ph->id + 1) % ph->shared_data->arguments[NUMBER_OF_PHILO]]);
		ph->state = SLEEPING;
		sleep_statement(ph);
		check_time(ph, get_time(), ph->shared_data->arguments[TIME_TO_SLEEP] / 1000, TIME_TO_SLEEP);
	}
	return (NULL);
}

void	run_philosophers(t_philosopher *ph)
{
	int 	iter;

	iter = -1;
	while (++iter < ph->shared_data->arguments[NUMBER_OF_PHILO])
	{
		pthread_create(&ph[iter].thread, NULL, philosopher_function, &ph[iter]);
		usleep(100);
	}
}

void	wait4philosophers(t_philosopher *ph)
{
		int 	iter;

	iter = 0;
	while (iter < ph->shared_data->arguments[NUMBER_OF_PHILO])
	{
		pthread_join(ph[iter].thread, NULL);
		iter++;
	}	
}

int		check4errors(int argc, char **argv)
{
	int		iterator;
	int		nested_iter;

	if (argc < 5 || argc > 6)
		return (1);
	iterator = 1;
	while (iterator < argc)
	{
		nested_iter = 0;
		while (argv[iterator][nested_iter])
		{
			if (!isdigits(argv[iterator][nested_iter]))
				return (1);
			nested_iter++;
		}
		iterator++;
	}
	return (0);
}

int		main(int argc, char *argv[])
{
	t_philosopher	*ph;
	struct s_global		*shared_data;

	shared_data = malloc(sizeof(struct s_global));
	if (check4errors(argc, argv))
	{
		ft_putstr("arguments error\n");
		return (1);
	}
	init_global_var(shared_data, argc, argv);
	/*printf("program start %lld\n", shared_data->program_start);
	printf("time eat %lld\n", shared_data->arguments[TIME_TO_EAT]);
	printf("time to sleep %lld\n", shared_data->arguments[TIME_TO_SLEEP]);
	printf("time to die %lld\n", shared_data->arguments[TIME_TO_DIE]);
	printf("number of philosophers %lld\n", shared_data->arguments[NUMBER_OF_PHILO]);
	*/
	ph = init_philosophers(shared_data);
	run_philosophers(ph);
	checker_state(ph);
	if (!shared_data->someone_died)
		wait4philosophers(ph);

	free(shared_data->forks);
	free(ph);
	return (0);
}
