#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "libft.h"

void	mod_str(char ***str_arr)
{
	*(str_arr[0]) = "XXX";
}

int	main(void)
{
	char	**arr_string;
	int		i;

	arr_string = ft_split("abc   def ghi", ' ');
	i = 0;
	while(arr_string[i])
	{
		printf("%s\n", arr_string[i]);
		i++;
	}
	mod_str(&arr_string);
	i = 0;
	while(arr_string[i])
	{
		printf("%s\n", arr_string[i]);
		i++;
	}
	return (0);
}
