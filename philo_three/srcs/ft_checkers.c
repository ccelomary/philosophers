/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-omar <mel-omar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 14:05:12 by mel-omar          #+#    #+#             */
/*   Updated: 2021/05/26 21:16:05 by mel-omar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

long long 	difference_ab(long long a, long long b)
{
	return (a - b);
}

void	check_time(t_philosopher *ph, long long t, long long duration, int type)
{
	usleep(ph->shared_data->arguments[type] - 30000);
	while ((get_time() - t) * 1000 < duration);
}
