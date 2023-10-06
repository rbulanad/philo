#include "philo.h"

int	args_checker(char **argv)
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

void	*print_hello()
{
	printf("hello im thread\n");
	return NULL;
}

int	main(int argc, char **argv)
{
	t_args		arg;
	struct timeval	time;
	struct timeval	time2;

	if (argc == 5)
	{
		gettimeofday(&time, NULL);
		if (args_checker(argv) == 1)
		{
			printf("ERROR: WRONG ARGS\n");
			return (1);
		}
		if ((arg.num_philo = atoi(argv[1])) < 1)
		{
			printf("ERROR: WRONG ARGS\n");
			return (1);
		}
		usleep(2000000);
		gettimeofday(&time2, NULL);
		printf("program time = %ld ms\n", (time2.tv_sec - time.tv_sec) * 1000);
		/*arg.t_die = atoi(argv[2]);
		arg.t_eat = atoi(argv[3]);
		arg.t_sleep = atoi(argv[4]);
		printf("num philo = %d\nt_die = %d\nt_eat = %d\nt_sleep = %d\n", arg.num_philo, arg.t_die, arg.t_eat, arg.t_sleep);*/
	}
	else
		printf("ERROR: NUM ARGS\n");
}
