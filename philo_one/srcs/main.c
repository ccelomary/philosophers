/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-omar <mel-omar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 17:04:42 by mel-omar          #+#    #+#             */
/*   Updated: 2021/05/28 18:25:28 by mel-omar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"
#include <stdio.h>

void	run_philosophers(t_philosopher *ph)
{
	int		iter;

	iter = -1;
	while (++iter < ph->shared_data->arguments[NUMBER_OF_PHILO])
	{
		pthread_create(&ph[iter].thread, NULL, philosopher_function, &ph[iter]);
		usleep(100);
	}
}

void	wait4philosophers(t_philosopher *ph)
{
	int	iter;

	iter = 0;
	while (iter < ph->shared_data->arguments[NUMBER_OF_PHILO])
	{
		pthread_join(ph[iter].thread, NULL);
		iter++;
	}	
}

int	main(int argc, char *argv[])
{
	t_philosopher		*ph;
	struct s_global		*shared_data;

	shared_data = malloc(sizeof(struct s_global));
	if (check4errors(argc, argv))
	{
		ft_print_error("arguments error\n");
		return (1);
	}
	if (init_global_var(shared_data, argc, argv))
	{
		ft_print_error("arguments error\n");
		return (1);
	}
	shared_data->program_start = get_time();
	ph = init_philosophers(shared_data);
	run_philosophers(ph);
	checker_state(ph);
	wait4philosophers(ph);
	free(shared_data->forks);
	free(ph);
	free(shared_data);
	return (0);
}
