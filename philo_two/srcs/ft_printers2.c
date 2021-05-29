/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printers2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-omar <mel-omar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 21:36:42 by mel-omar          #+#    #+#             */
/*   Updated: 2021/05/29 21:51:12 by mel-omar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	eat_statement(t_philosopher *philo)
{
	sem_wait(philo->shared_data->output_manger);
	if (!philo->shared_data->someone_died)
	{
		ft_putnbr(convert(get_time() - philo->shared_data->program_start));
		ft_putc(' ');
		ft_putnbr(philo->id + 1);
		ft_putstr(" is eating");
		endl();
	}
	sem_post(philo->shared_data->output_manger);
}

void	think_statement(t_philosopher *philo)
{
	sem_wait(philo->shared_data->output_manger);
	if (!philo->shared_data->someone_died)
	{
		ft_putnbr(convert(get_time() - philo->shared_data->program_start));
		ft_putc(' ');
		ft_putnbr(philo->id + 1);
		ft_putstr(" is thinking");
		endl();
	}
	sem_post(philo->shared_data->output_manger);
}

void	sleep_statement(t_philosopher *philo)
{
	sem_wait(philo->shared_data->output_manger);
	if (!philo->shared_data->someone_died)
	{
		ft_putnbr(convert(get_time() - philo->shared_data->program_start));
		ft_putc(' ');
		ft_putnbr(philo->id + 1);
		ft_putstr(" is sleeping");
		endl();
	}
	sem_post(philo->shared_data->output_manger);
}

void	fork_statement(t_philosopher *philo)
{
	sem_wait(philo->shared_data->output_manger);
	if (!philo->shared_data->someone_died)
	{
		ft_putnbr(convert(get_time() - philo->shared_data->program_start));
		ft_putc(' ');
		ft_putnbr(philo->id + 1);
		ft_putstr(" has taken a fork");
		endl();
	}
	sem_post(philo->shared_data->output_manger);
}

void	death_statement(t_philosopher *philo)
{
	sem_wait(philo->shared_data->output_manger);
	if (!philo->shared_data->someone_died)
	{
		ft_putnbr(convert(get_time() - philo->shared_data->program_start));
		ft_putc(' ');
		ft_putnbr(philo->id + 1);
		philo->shared_data->someone_died = 1;
		ft_putstr(" died\n");
	}
	sem_post(philo->shared_data->output_manger);
}
