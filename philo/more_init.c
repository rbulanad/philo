/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:53:09 by rbulanad          #+#    #+#             */
/*   Updated: 2024/03/05 14:23:22 by rbulanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	more_init(t_data *d)
{
	int	i;

	i = -1;
	while (++i < d->num_philo)
	{
		d->last_meal[i] = d->start;
		d->ate[i] = 0;
		pthread_mutex_init(&d->forks[i], NULL);
		(d->hands[i] = malloc(sizeof(int) * 2));
		if (!(d->hands[i]))
			return (printf("ERROR: MALLOC\n"), 1);
		d->hands[i][0] = i;
		d->hands[i][1] = (i + 1) % d->num_philo;
		if (i % 2)
		{
			d->hands[i][0] = (i + 1) % d->num_philo;
			d->hands[i][1] = i;
		}
	}
	pthread_mutex_init(&d->write, NULL);
	pthread_mutex_init(&d->stap, NULL);
	pthread_mutex_init(&d->read, NULL);
	return (0);
}

int	mallox(t_data *d)
{
	d->tid = malloc(sizeof(pthread_t) * d->num_philo);
	d->last_meal = malloc(sizeof(long) * d->num_philo);
	d->ate = malloc(sizeof(int) * d->num_philo);
	d->hands = malloc(sizeof(int *) * d->num_philo);
	d->forks = malloc(sizeof(pthread_mutex_t) * d->num_philo);
	if (!(d->tid) || !(d->last_meal) || !(d->ate)
		|| !(d->hands) || !(d->forks))
		return (printf("ERROR: MALLOC\n"), 1);
	return (0);
}

int	ft_data_init(t_data *d, char **argv)
{
	d->num_philo = ft_atol(argv[1]);
	if (d->num_philo == 0 || d->num_philo > 2147483647)
		return (printf("ERROR2: WRONG ARGS\n"), 1);
	d->t_die = ft_atol(argv[2]);
	if (d->t_die == 0 || d->t_die > 2147483647)
		return (printf("ERROR2: WRONG ARGS\n"), 1);
	d->t_eat = ft_atol(argv[3]);
	if (d->t_eat == 0 || d->t_eat > 2147483647)
		return (printf("ERROR2: WRONG ARGS\n"), 1);
	d->t_sleep = ft_atol(argv[4]);
	if (d->t_sleep == 0 || d->t_sleep > 2147483647)
		return (printf("ERROR2: WRONG ARGS\n"), 1);
	if (argv[5])
	{
		d->num_eat = ft_atol(argv[5]);
		if (d->num_eat == 0 || d->num_eat > 2147483647)
			return (printf("ERROR2: WRONG ARGS\n"), 1);
	}
	else
		d->num_eat = -1;
	d->stop = 0;
	d->start = ft_gettime();
	if (mallox(d) == 1 || more_init(d) == 1)
		return (1);
	return (0);
}

void	ft_philo_creator(t_data *d)
{
	int	i;

	i = -1;
	while (++i < d->num_philo)
		pthread_create(&d->tid[i], NULL, (void *)routine, d);
}
