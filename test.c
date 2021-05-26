#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>

sem_t *semaphore;

void	*routine(void *th)
{
	printf("\nbefore\n");
	sem_wait(semaphore);
	printf("sem enter\n");
	usleep((unsigned long)100000000);
	printf("sem out\n");
	sem_post(semaphore);
	return (NULL);
}

int	main(void)
{
	pthread_t t1, t2;
	sem_unlink("sem/philo_two");
	semaphore = sem_open("sem/philo_two", O_CREAT, 0644, 1);
	pthread_create(&t1, NULL, routine, NULL);
	pthread_create(&t2, NULL, routine, NULL);
	printf("blabla bla\n");
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	return (0);
}