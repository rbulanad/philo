#include "philo.h"

int	ft_is_stap(t_data *d)
{
	int	stap;

	pthread_mutex_lock(&d->stap);
	stap = d->stop;
	pthread_mutex_unlock(&d->stap);
	return (stap);
}

void	ft_update_stap(t_data *d, int status)
{
	pthread_mutex_lock(&d->stap);
	d->stop = status;
	pthread_mutex_unlock(&d->stap);
}
