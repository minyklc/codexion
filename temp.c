//rm -f file 
#include "codexion.h"

void	print_helper(int limit, t_thread *stack)
{
	int	i;

	i = 0;
	while (i < limit)
	{
		printf("%i\n", stack[i].n);
		i++;
	}
}

void	*thread_create(void *arg)
{
	// int	*i;

	// i = (int *)arg;
	// // pthread_t tid = pthread_self();
	// printf("%i new thread created\n", *i);
	return (arg);
}
