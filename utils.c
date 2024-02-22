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

void	display(t_data *d, int num, char *str)
{
	if (d->stop == 0)
	{
		pthread_mutex_lock(&d->read);//READ LOCK
		printf("%ld ms philo %d %s\n", ft_gettime() - d->start, num, str);
		pthread_mutex_unlock(&d->read);//READ UNLOCK
	}
}

void	ft_eat(t_data *d, int current)
{
	pthread_mutex_lock(&d->forks[current]);//FORK LOCK
	display(d, current + 1, "has taken a fork");
	pthread_mutex_lock(&d->forks[(current + 1) % d->num_philo]);//FORK2 LOCK
	display(d, current + 1, "has taken a fork");
	display(d, current + 1, "is eating");
	pthread_mutex_lock(&d->write);//WRITE LOCK
	d->last_meal[current] = ft_gettime();
	pthread_mutex_unlock(&d->write);//WRITE UNLOCK
	ft_sleep(d->t_eat);
	pthread_mutex_lock(&d->write);//WRITE LOCK
	d->ate[current]++;
	pthread_mutex_unlock(&d->write);//WRITE UNLOCK
	pthread_mutex_unlock(&d->forks[current]);//FORK UNLOCK
	pthread_mutex_unlock(&d->forks[(current + 1) % d->num_philo]);//FORK2 UNLOCK
	display(d, current + 1, "is sleeping");
	ft_sleep(d->t_sleep);
	display(d, current + 1, "is thinking");
	
}

int	ft_check_death(t_data *d)
{
	int		i;
	long	diff;

	i = -1;
	while (++i < d->num_philo)
	{
		pthread_mutex_lock(&d->write);//WRITE LOCK
		diff = ft_gettime() - d->last_meal[i];
		pthread_mutex_unlock(&d->write);//WRITE UNLOCK
		if (diff >= d->t_die)
		{
			d->stop = 1;
			return(printf("%ld ms philo %d died\n", ft_gettime() - d->start, i), 1);
		}
		if (ft_check_ate(d) == 0)
		{
			d->stop = 1;
			return(printf("everyone ate\n"), 1);
		}
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

void	ft_safe_exit(t_data *d)
{
	pthread_mutex_destroy(&d->write);
	pthread_mutex_destroy(&d->philo);
	pthread_mutex_destroy(&d->read);
	free(d->tid);
	free(d->last_meal);
	free(d->forks);
	free(d->ate);
}
