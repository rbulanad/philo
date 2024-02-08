/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:20:43 by rbulanad          #+#    #+#             */
/*   Updated: 2024/02/08 16:01:12 by rbulanad         ###   ########.fr       */
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

int	ft_data_init(t_data *d, char **argv)
{
	if ((d->num_philo = ft_atol(argv[1])) == 0 || d->t_eat > 2147483647)
		return (1);
	if ((d->t_die = ft_atol(argv[2])) == 0 || d->t_eat > 2147483647)
		return (1);
	if ((d->t_eat = ft_atol(argv[3])) == 0 || d->t_eat > 2147483647)
		return (1);
	if ((d->t_sleep = ft_atol(argv[4])) == 0 || d->t_eat > 2147483647)
		return (1);
	if (argv[5])
	{
		if ((d->num_eat = ft_atol(argv[5])) == 0 || d->t_eat > 2147483647)
			return (1);
	}
	else
		d->num_eat = -1;
	return (0);
}

void	*routine(t_data *d)
{
	(void)d;
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data	d;
	struct	timeval time;

	if (argc == 5 || argc == 6)
	{
		gettimeofday(&time, NULL);
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
		pthread_create(&d.tid, NULL, (void*)routine, &d);
		pthread_join(d.tid, NULL);
		printf("%ld %ld %ld %ld\n", d.num_philo, d.t_die, d.t_eat, d.t_sleep);
		//gettimeofday(&time2, NULL);
		//printf("prog time = %ld ms\n", (time2.tv_usec - time.tv_usec) / 1000);
	}
	else
		printf("ERROR: NUM ARGS");
	return (0);
}
