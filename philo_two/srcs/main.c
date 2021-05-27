/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-omar <mel-omar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 17:04:42 by mel-omar          #+#    #+#             */
/*   Updated: 2021/05/27 15:08:57 by mel-omar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	run_philosophers(t_philosopher *ph)
{
	int	iter;

	iter = -1;
	while (++iter < ph->shared_data->arguments[NUMBER_OF_PHILO])
		pthread_create(&ph[iter].thread, NULL, philosopher_function, &ph[iter]);
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
		ft_putstr("arguments error\n");
		return (1);
	}
	init_global_var(shared_data, argc, argv);
	ph = init_philosophers(shared_data);
	run_philosophers(ph);
	checker_state(ph);
	if (!shared_data->someone_died)
		wait4philosophers(ph);
	free(ph);
	free(shared_data);
	return (0);
}
