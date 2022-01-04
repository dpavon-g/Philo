#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


typedef	struct s_dates
{	
	pthread_mutex_t     *forks;
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
	pthread_mutex_lock(&dates->forks[1]);
	printf("Philo %d take fork1\n", dates->i);
	pthread_mutex_lock(&dates->forks[2]);
	printf("Philo %d take fork2\n", dates->i);
	printf("Philo %d is eatting\n", dates->i);
	dates->i++;
	pthread_mutex_unlock(&dates->forks[2]);
	pthread_mutex_unlock(&dates->forks[1]);
	pthread_mutex_unlock(&dates->forks[0]);
	
}

int main()
{
	t_dates		dates;
	pthread_t	*hilos;
	int			i;
	int			number;

	number = 10;
	dates.contador = 0;

	dates.forks = malloc(sizeof(pthread_mutex_t) * number);
	pthread_mutex_init(&dates.forks[0], NULL);
	pthread_mutex_init(&dates.forks[1], NULL);
	pthread_mutex_init(&dates.forks[2], NULL);
	hilos = malloc(sizeof(pthread_t) * number);
	dates.i = 0;
	while (dates.i < number)
	{
		pthread_mutex_init(&dates.forks[dates.i], NULL);
		dates.i++;
	}
	dates.i = 0;
	while (dates.i < number)
	{
		pthread_mutex_lock(&dates.forks[0]);
		pthread_create(&hilos[dates.i], NULL, birth_philo, (void *)&dates);
	}
	i = 0;
	while (i < number)
	{
		pthread_join(hilos[i], NULL);
		i++;
	}
	free(dates.forks);
	free(hilos);
}