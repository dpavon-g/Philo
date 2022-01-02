#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef	struct s_dates
{
	pthread_mutex_t     *mutex;
	int					contador;
	int					i;
}	t_dates;

void    *function1(void *args)
{
	t_dates *dates;

	dates = (t_dates*)args;
	int	i;

	i = 0;
	while (i < 10000)
	{
		pthread_mutex_lock(&dates->mutex[0]);
		i++;
		dates->contador++;
		pthread_mutex_unlock(&dates->mutex[0]);
	}
}

void    *function2(void *args)
{
	t_dates *dates;

	dates = (t_dates*)args;
	int	i;

	i = 0;
	while (i < 10000)
	{
		pthread_mutex_lock(&dates->mutex[0]);
		i++;
		dates->contador--;
		pthread_mutex_unlock(&dates->mutex[0]);
	}
}

int main()
{
	t_dates		dates;
	pthread_t	*hilos;
	int			number;
	int			i;

	dates.i = 0;
	number = 4;
	dates.contador = 0;
	dates.mutex = malloc(sizeof(pthread_mutex_t) * number);
	while (dates.i < number)
	{
		pthread_mutex_init(&dates.mutex[dates.i], NULL);
		dates.i++;
	}
	hilos = malloc(sizeof(pthread_t) * number);
	dates.i = 0;
	while (dates.i < number)
	{
		pthread_create(&hilos[dates.i], NULL, function1, (void *)&dates);
		dates.i++;
	}
	dates.i = 0;
	while (dates.i < number)
	{
		pthread_join(hilos[dates.i], NULL);
		dates.i++;
	}
	free(hilos);
	printf("Valor del contador: %d\n", dates.contador);
}