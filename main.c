/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:20:43 by rbulanad          #+#    #+#             */
/*   Updated: 2024/02/21 19:08:43 by rbulanad         ###   ########.fr       */
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
	if ((d->num_philo = ft_atol(argv[1])) == 0 || d->num_philo > 2147483647)
		return (1);
	if ((d->t_die = ft_atol(argv[2])) == 0 || d->t_die > 2147483647)
		return (1);
	if ((d->t_eat = ft_atol(argv[3])) == 0 || d->t_eat > 2147483647)
		return (1);
	if ((d->t_sleep = ft_atol(argv[4])) == 0 || d->t_sleep > 2147483647)
		return (1);
	if (argv[5]) //optional arg
	{
		if ((d->num_eat = ft_atol(argv[5])) == 0 || d->num_eat > 2147483647)
			return (1);
	}
	else
		d->num_eat = -1;
	d->stop = 0;
	d->start = ft_gettime();
	d->tid = malloc(sizeof(pthread_t) * d->num_philo);
	d->last_meal = malloc(sizeof(long) * d->num_philo);
	d->ate = malloc(sizeof(int) * d->num_philo);
	d->forks = malloc(sizeof(pthread_mutex_t) * d->num_philo);
	int	i = -1; /////////////////
	while (++i < d->num_philo)
	{
		d->last_meal[i] = d->start;
		d->ate[i] = 0;
		pthread_mutex_init(&d->forks[i], NULL);
	}
	pthread_mutex_init(&d->write, NULL);
	pthread_mutex_init(&d->read, NULL);
	pthread_mutex_init(&d->philo, NULL);
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
	static int	i;
	int			current;


	if (d->num_philo == 1)
	{
		display(d, 1, "has taken a fork");
		ft_sleep(d->t_die);
	}
	else
	{
		pthread_mutex_lock(&d->philo);//PHILO LOCK
		current = i++;
		pthread_mutex_unlock(&d->philo);//PHILO UNLOCK
		if (current % 2)
			ft_sleep(60);
		while (d->stop == 0 && d->ate[current] != d->num_eat)
			ft_eat(d, current);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data	d;

	if (argc == 5 || argc == 6)
	{
		if (parser(argv) == 1)
		{
			printf("ERROR: WRONG ARGS\n");
			return (1);
		}
		if (ft_data_init(&d, argv) == 1)
		{
			printf("ERROR2: WRONG ARGS\n");
			return (1);
		}
		ft_philo_creator(&d);
		while (1)
			if (ft_check_death(&d))
			{
				ft_safe_exit(&d);
				return (0);
			}
	}
	else
		printf("ERROR: NUM ARGS\n");
	return (0);
}
