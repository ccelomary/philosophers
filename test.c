#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

void print_str(char *s)
{
	write(1, s, sizeof(char) * strlen(s));
}

pthread_mutex_t mutex;

void		*test_function(void *d)
{
	int v = *((int *)d)  + 48;
	for (int i = 0; i < 3; i++)
	{
		print_str("one\n");
		write(1, &v, sizeof(int));
		print_str("\n");
		pthread_mutex_lock(&mutex);
		print_str("hello world\n");
		sleep(6);
		pthread_mutex_unlock(&mutex);
		print_str("goodbye\n");
	}
	return (NULL);
}

int	main(void)
{
	pthread_t thread[3];
	int id[3] = {0, 1, 2};
	pthread_mutex_init(&mutex, 0);
	for (int i = 0; i < 3; i++)
	{
		pthread_create(&thread[i], 0, test_function, &id[i]);
	}
	for (int i =0; i < 3;i++)
		pthread_join(thread[i], 0);
}