#include <pthread.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int	function()
{
	char	*unused;
	int		*test;

	test = NULL;
	*test = 1;
	return (0);
}

int main(void)
{
	printf("testing linter again\n");
	function();
	function();
	return (0);
}
