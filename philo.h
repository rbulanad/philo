/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:30:04 by rbulanad          #+#    #+#             */
/*   Updated: 2024/02/13 11:01:17 by rbulanad         ###   ########.fr       */
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
void	*routine(t_data *d);

typedef struct	s_data
{
	long		num_philo;
	long		t_die;
	long		t_eat;
	long		t_sleep;
	long		num_eat;
	long		last_meal;
	long		start;
	long		ph_count;
	int		ate;
	pthread_t	tid;
	pthread_mutex_t	read;
	pthread_mutex_t	write;
}		t_data;

#endif
