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
