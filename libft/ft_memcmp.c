/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 11:20:27 by amarchal          #+#    #+#             */
/*   Updated: 2021/11/09 12:12:11 by amarchal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*buff1;
	const unsigned char	*buff2;

	i = 0;
	buff1 = s1;
	buff2 = s2;
	while (i < n)
	{
		if (buff1[i] != buff2[i])
			return (buff1[i] - buff2[i]);
		i++;
	}
	return (0);
}
