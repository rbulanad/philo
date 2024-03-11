/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:30:04 by rbulanad          #+#    #+#             */
/*   Updated: 2024/03/06 13:52:45 by rbulanad         ###   ########.fr       */
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
long	ft_gettime(void);

typedef struct s_data
{
	long			num_philo;
	long			t_die;
	long			t_eat;
	long			t_sleep;
	long			num_eat;
	long			start;
	int				current;
	long			*last_meal;
	int				*ate;
	int				stop;
	int				**hands;
	pthread_t		*tid;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	pthread_mutex_t	read;
	pthread_mutex_t	stap;
}		t_data;

void	ft_sleep(t_data *d, long time);
int		ft_data_init(t_data *d, char **argv);
int		more_init(t_data *d);
void	*routine(t_data *d);
void	ft_philo_creator(t_data *d);
int		ft_check_death(t_data *d);
int		ft_check_ate(t_data *d);
void	ft_eat(t_data *d, int current);
void	display(t_data *d, int num, char *str, int bypass);
void	ft_safe_exit(t_data *d);
void	ft_update_stap(t_data *d, int status);
int		ft_is_stap(t_data *d);

#endif
