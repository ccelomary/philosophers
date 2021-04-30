/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-omar <mel-omar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 16:55:07 by mel-omar          #+#    #+#             */
/*   Updated: 2021/04/29 22:51:49 by mel-omar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>
# define NUMBER_OF_PHILO 0
# define TIME_TO_DIE 1
# define TIME_TO_EAT 2
# define TIME_TO_SLEEP 3
# define NUMBER_MUST_EAT 4

typedef enum e_state
{
	THINKING,
	SLEEPING,
	EATING
}			t_state;

typedef struct s_philosopher
{
	int			id;
	int			time_eat;
	int			last_time_eat;
	pthread_t	thread;
	t_state		state;
}				t_philosopher;

struct s_global
{
	int					arguments[5];
	int					program_start;
	int					someone_died;
	int					all_eat;
	pthread_mutex_t		*forks;
	pthread_mutex_t		output_manger;
}						g_global_var;

int				isdigits(char c);
int				string2number(const char *string);
long			get_time(void);
void			ft_putc(char c);
void			ft_putnbr(unsigned int number);
void			ft_putstr(const char *str);
void			endl(void);
void 			eat_statement(t_philosopher *philo);
void 			think_statement(t_philosopher * philo);
void 			sleep_statement(t_philosopher * philo);
void 			fork_statement(t_philosopher * philo);
void			init_global_var(int argc, char *argv[]);
void 			death_statement(t_philosopher * philo);
t_philosopher	*init_philosophers(void);
#endif