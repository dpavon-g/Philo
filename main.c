#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


typedef	struct s_dates
{	
	pthread_mutex_t     fork1;
	pthread_mutex_t     fork2;
	int					contador;
	int					i;
}	t_dates;

void    *birth_philo(void *args)
{
	t_dates *dates;
	int		total;

	total = 0;
	dates = (t_dates*)args;

	// usleep(1000 * dates->i);

	// pthread_mutex_lock(&dates->fork1);
	printf("Philo %d\n", dates->i);
	// pthread_mutex_unlock(&dates->fork1);
	pthread_mutex_unlock(&dates->fork2);
	
}

int main()
{
	t_dates		dates;
	pthread_t	*hilos;
	int			i;
	int			number;

	number = 2;
	dates.contador = 0;

	pthread_mutex_init(&dates.fork1, NULL);
	pthread_mutex_init(&dates.fork2, NULL);
	hilos = malloc(sizeof(pthread_t) * number);
	dates.i = 0;
	while (dates.i < number)
	{
		pthread_mutex_lock(&dates.fork2);
		pthread_create(&hilos[dates.i], NULL, birth_philo, (void *)&dates);
		dates.i++;
	}

	dates.i = 0;
	// while (dates.i < number)
	// {
	// 	pthread_join(hilos[dates.i], NULL);
	// 	dates.i++;
	// }
	pthread_join(hilos[0], NULL);
	pthread_join(hilos[1], NULL);
	// pthread_join(hilos[2], NULL);
	// pthread_join(hilos[3], NULL);
	// pthread_join(hilos[4], NULL);
	free(hilos);
}