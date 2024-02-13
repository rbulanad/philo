#include "philo.h"

void	ft_sleep(long time)
{
	long	i;

	i = -1;
	while (++i <= time)
		usleep(1000);
}

void	ft_philo_creator(t_data *d)
{
	while (d->ph_count <= d->num_philo)
	{
		pthread_create(&d.tid, NULL, (void*)routine, &d);
		pthread_mutex_lock(d->write);
		d->ph_count++;
		pthread_mutex_unlock(d->write);
	}
}
