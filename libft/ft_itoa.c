/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 16:42:42 by amarchal          #+#    #+#             */
/*   Updated: 2021/11/10 11:49:47 by amarchal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_fillstr(char *str, int n, int wordsize)
{
	long int	nbr;

	nbr = n;
	if (nbr < 0)
	{
		str[0] = '-';
		nbr *= -1;
	}
	str[wordsize] = '\0';
	wordsize--;
	if (nbr == 0)
		str[wordsize] = '0';
	while (nbr > 0)
	{
		str[wordsize] = nbr % 10 + '0';
		nbr /= 10;
		wordsize--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	int			i;
	int			wordsize;
	char		*str;
	long int	nbr;

	i = 0;
	wordsize = 0;
	nbr = n;
	if (nbr <= 0)
	{
		nbr *= -1;
		wordsize++;
	}
	while (nbr > 0)
	{
		nbr /= 10;
		wordsize++;
	}
	str = malloc(sizeof(char) * (wordsize + 1));
	if (!str)
		return (NULL);
	str = ft_fillstr(str, n, wordsize);
	return (str);
}
