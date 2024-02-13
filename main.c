/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:20:43 by rbulanad          #+#    #+#             */
/*   Updated: 2024/02/13 10:53:39 by rbulanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parser(char **argv)
{

	int	i;
	int	j;

	i = 0;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
		{
			if (argv[i][j] < 48 || argv[i][j] > 57)
				return (1);
		}
	}
	return (0);
}

int	ft_data_init(t_data *d, char **argv) //some parsing for int max in here
{
	if ((d->num_philo = ft_atol(argv[1])) == 0 || d->t_eat > 2147483647)
		return (1);
	if ((d->t_die = ft_atol(argv[2])) == 0 || d->t_eat > 2147483647)
		return (1);
	if ((d->t_eat = ft_atol(argv[3])) == 0 || d->t_eat > 2147483647)
		return (1);
	if ((d->t_sleep = ft_atol(argv[4])) == 0 || d->t_eat > 2147483647)
		return (1);
	if (argv[5]) //optional arg
	{
		if ((d->num_eat = ft_atol(argv[5])) == 0 || d->t_eat > 2147483647)
			return (1);
	}
	else
		d->num_eat = -1;
	d->ate = 0;
	d->ph_count = 0;
	d->last_meal = d->start;
	return (0);
}

long	ft_gettime()
{
	long	ret;
	struct	timeval t;

	gettimeofday(&t, NULL);
	ret = (t.tv_sec * 1000) + (t.tv_usec / 1000);

	return (ret);
}

void	*routine(t_data *d)
{
	while (d->ate < 1)
	{
		pthread_mutex_lock(&d->write);
		d->last_meal = ft_gettime();
		pthread_mutex_lock(&d->read);
		printf("%ld ms PHILO is eating\n", d->last_meal - d->start);
		d->ate += 1;
		pthread_mutex_unlock(&d->write);
		pthread_mutex_unlock(&d->read);
		ft_sleep(d->t_eat);
	}

	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data	d;

	if (argc == 5 || argc == 6)
	{
		d.start = ft_gettime();
		if (parser(argv) == 1)
		{
			printf("ERROR: WRONG ARGS\n");
			return (1);
		}
		if (ft_data_init(&d, argv) == 1)
		{
			printf("ERROR: WRONG ARGS\n");
			return (1);
		}
		ft_philo_creator();
		pthread_create(&d.tid, NULL, (void*)routine, &d);
		while (1)
		{
			if ((d.last_meal - d.start) >= d.t_die)
			{
				pthread_mutex_unlock(&d.read);
				printf("%ldms PHILO died\n", d.last_meal - d.start);
				pthread_mutex_unlock(&d.read);
				return (1);
			}
			if (d.ate > 0)
			{
				pthread_mutex_lock(&d.read);
				printf("END\n");
				pthread_mutex_unlock(&d.read);
				return (0);
			}
		}
	}
	else
		printf("ERROR: NUM ARGS");
	return (0);
}
