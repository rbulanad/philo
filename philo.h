/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:30:04 by rbulanad          #+#    #+#             */
/*   Updated: 2024/02/21 18:04:23 by rbulanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

long	ft_atol(char *str);
void	ft_sleep(long time);
long	ft_gettime();

typedef struct	s_data
{
	long			num_philo;
	long			t_die;
	long			t_eat;
	long			t_sleep;
	long			num_eat;
	long			start;
	int			current;
	long			*last_meal;
	int			*ate;
	int			stop;
	pthread_t		*tid;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	pthread_mutex_t	read;
	pthread_mutex_t	philo;
}		t_data;

void	*routine(t_data *d);
void	ft_philo_creator(t_data *d);
int	ft_check_death(t_data *d);
int	ft_check_ate(t_data *d);
void	ft_eat(t_data *d, int current);
void	display(t_data *d, int num, char *str);
void	ft_safe_exit(t_data *d);
#endif
