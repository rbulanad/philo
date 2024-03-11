/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:20:43 by rbulanad          #+#    #+#             */
/*   Updated: 2024/03/06 13:59:03 by rbulanad         ###   ########.fr       */
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

void	ft_sleep(t_data *d, long time)
{
	long	end;

	if (ft_is_stap(d))
		return ;
	end = ft_gettime() + time;
	while (ft_gettime() < end)
		usleep(10);
}

long	ft_gettime(void)
{
	long			ret;
	struct timeval	t;

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
		display(d, 1, "has taken a fork", 0);
		ft_sleep(d, d->t_die);
	}
	else
	{
		pthread_mutex_lock(&d->read);
		current = i++;
		pthread_mutex_unlock(&d->read);
		if (current % 2)
			ft_sleep(d, 60);
		while (ft_check_ate(d) != 0)
		{
			if (ft_is_stap(d))
				break ;
			ft_eat(d, current);
		}
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data	d;

	if (argc == 5 || argc == 6)
	{
		if (parser(argv) == 1)
			return (printf("ERROR: WRONG ARGS\n"), 1);
		if (ft_data_init(&d, argv) == 1)
			return (1);
		ft_philo_creator(&d);
		while (1)
		{
			if (ft_check_death(&d))
				break ;
			ft_sleep(&d, 1);
		}
		ft_safe_exit(&d);
	}
	else
		printf("ERROR: NUM ARGS\n");
	return (0);
}
