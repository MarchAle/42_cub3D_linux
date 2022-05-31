/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 15:40:47 by amarchal          #+#    #+#             */
/*   Updated: 2021/11/10 13:31:09 by amarchal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	src_size;
	size_t	dest_size;

	i = 0;
	j = 0;
	src_size = ft_strlen(src);
	dest_size = ft_strlen(dest);
	if (dstsize == 0 || dstsize < dest_size)
		return (src_size + dstsize);
	if (src_size == 0)
		return (dest_size);
	while (dest[i])
	{
		i++;
	}
	while (src[j] && dest_size + j < dstsize - 1)
	{
		dest[dest_size + j] = src[j];
		j++;
	}
	dest[dest_size + j] = '\0';
	return (src_size + dest_size);
}
