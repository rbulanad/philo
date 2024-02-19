#include "philo.h"

void	ft_sleep(long time)
{
	long	save;

	save = ft_gettime();
	while (ft_gettime() != (save + time))
		usleep(1);
}

void	ft_philo_creator(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->num_philo)
	{
		pthread_create(&d->tid[i], NULL, (void*)routine, d);
		i++;
	}
}

int	ft_check_death(t_data *d)
{
	int		i;
	long	diff;

	i = -1;
	while (++i < d->num_philo)
	{
		pthread_mutex_lock(&d->write);
		diff = ft_gettime() - d->last_meal[i];
		if (diff >= d->t_die)
		{
			printf("%ld ms philo %d died\n", ft_gettime() - d->start, i);
			pthread_mutex_unlock(&d->write);
			return (1);
		}
		if (ft_check_ate(d) == 0)
			return(printf("everyone ate\n"), 1);
		pthread_mutex_unlock(&d->write);
	}
	return (0);
}

int	ft_check_ate(t_data *d)
{
	int	i;

	i = -1;
	while(++i < d->num_philo)
	{
		if (d->ate[i] != d->num_eat)
			return (1);
	}
	return (0);
}
