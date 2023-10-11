# include "minishell.h"

int	main(void)
{
	char	dst[20] = {0};
	char	src[] = "123";

	ft_strlcpy(dst, src, 4);
	ft_strlcat(dst, src, ft_strlen(dst) + ft_strlen(src) + 2);
	printf("length of src = %lu\n", ft_strlen(src));
	printf("%s\n", dst);
	return (0);
}
