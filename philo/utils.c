/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:49:59 by rbulanad          #+#    #+#             */
/*   Updated: 2024/03/05 14:43:37 by rbulanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	display(t_data *d, int num, char *str)
{
	pthread_mutex_lock(&d->stap);
	if (d->stop == 0)
	{
		pthread_mutex_lock(&d->read);
		printf("%ld %d %s\n", ft_gettime() - d->start, num, str);
		pthread_mutex_unlock(&d->read);
	}
	pthread_mutex_unlock(&d->stap);
}

void	ft_eat(t_data *d, int current)
{
	int	fork_l;
	int	fork_r;

	fork_l = d->hands[current][0];
	fork_r = d->hands[current][1];
	pthread_mutex_lock(&d->forks[fork_l]);
	display(d, current + 1, "has taken a fork");
	pthread_mutex_lock(&d->forks[fork_r]);
	display(d, current + 1, "has taken a fork");
	display(d, current + 1, "is eating");
	pthread_mutex_lock(&d->write);
	d->last_meal[current] = ft_gettime();
	if (d->ate[current] < d->num_eat)
		d->ate[current]++;
	pthread_mutex_unlock(&d->write);
	ft_sleep(d->t_eat);
	pthread_mutex_unlock(&d->forks[fork_l]);
	pthread_mutex_unlock(&d->forks[fork_r]);
	display(d, current + 1, "is sleeping");
	ft_sleep(d->t_sleep);
	display(d, current + 1, "is thinking");
}

int	ft_check_death(t_data *d)
{
	long	diff;
	int		i;

	i = -1;
	while (++i < d->num_philo)
	{
		pthread_mutex_lock(&d->write);
		diff = ft_gettime() - d->last_meal[i];
		pthread_mutex_unlock(&d->write);
		if (diff > d->t_die)
		{
			printf("%ld %d died\n", ft_gettime() - d->start, i + 1);
			pthread_mutex_lock(&d->stap);
			d->stop = 1;
			return (pthread_mutex_unlock(&d->stap), 1);
		}
		if (ft_check_ate(d) == 0)
		{
			pthread_mutex_lock(&d->stap);
			d->stop = 1;
			return (pthread_mutex_unlock(&d->stap), 1);
		}
	}
	return (0);
}

int	ft_check_ate(t_data *d)
{
	int	i;
	int	ate;

	i = -1;
	while (++i < d->num_philo)
	{
		pthread_mutex_lock(&d->write);
		ate = d->ate[i];
		pthread_mutex_unlock(&d->write);
		if (ate != d->num_eat)
			return (1);
	}
	return (0);
}

void	ft_safe_exit(t_data *d)
{
	int	i;

	i = -1;
	while (++i < d->num_philo)
		pthread_join(d->tid[i], NULL);
}
