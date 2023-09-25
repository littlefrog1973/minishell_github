#include <stdio.h>

int	add(int a, int b)
{
	return (a + b);
}

int minus(int a, int b)
{
	return (a - b);
}

void	init_fn_ptr(int (*fn_ptr[])(int, int))
{
	fn_ptr[0] = &add;
	fn_ptr[1] = &minus;
	fn_ptr[2] = NULL;
}

int	main(void)
{
	int	(*fn_ptr[3])(int, int);

	init_fn_ptr(fn_ptr);
	printf("a + b = %d\n", fn_ptr[0](10, 9));
	printf("a - b = %d\n", fn_ptr[1](10, 9));
}
