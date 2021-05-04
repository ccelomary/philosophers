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

int	main(void)
{
	pthread_t thread[3];
	int id[3] = {0, 1, 2};
	pthread_mutex_init(&mutex, 0);
	pthread_mutex_lock(&mutex);
	sleep(20);
	print_str("inside\n");
	pthread_mutex_unlock(&mutex);
	print_str("outside\n");
	return (0);
}