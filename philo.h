/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:30:04 by rbulanad          #+#    #+#             */
/*   Updated: 2024/02/08 15:58:37 by rbulanad         ###   ########.fr       */
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

typedef struct	s_data
{
	long		num_philo;
	long		t_die;
	long		t_eat;
	long		t_sleep;
	long		num_eat;
	pthread_t	tid;
}		t_data;

#endif
