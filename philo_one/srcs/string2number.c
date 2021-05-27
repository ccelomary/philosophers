/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string2number.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-omar <mel-omar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 16:58:39 by mel-omar          #+#    #+#             */
/*   Updated: 2021/05/27 14:45:40 by mel-omar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	isdigits(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

unsigned long long	string2number(const char *string)
{
	unsigned long long	number;
	int					sign;

	number = 0;
	sign = 1;
	if (!string)
		return (0);
	else if (*string == '+')
		string++;
	while (isdigits(*string))
	{
		number = (number * 10) + (int)(*string - 48);
		string++;
	}
	return (sign * number);
}
