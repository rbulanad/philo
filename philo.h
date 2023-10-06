#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct	s_args
{
	int	num_philo;
	int	t_die;
	int	t_eat;
	int	t_sleep;
}				t_args;

#endif
