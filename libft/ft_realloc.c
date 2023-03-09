#include "libft.h"

char	*ft_realloc(void *ptr, int new_size)
{
	char	*line;

	line = malloc(new_size);
	if (!line)
		return NULL;
	ft_memcpy(line, ptr, new_size - 1);
	free(ptr);
	return (line);
}