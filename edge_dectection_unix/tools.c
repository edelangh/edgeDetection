
#include "edge_detection.h"

void	ft_memcpy_uint(unsigned int* dest, unsigned int* src, unsigned int size)
{
	unsigned int i;

	i = 0;
	while (i < size)
	{
		dest[i] = src[i];
		++i;
	}
}
