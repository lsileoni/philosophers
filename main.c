#include <pthread.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int	function()
{
	int		*test;

	test = NULL;
	*test = 1;
	return (0);
}

int main(void)
{
	printf("testing linter again\n");
	function();
	return (0);
}
