/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 15:16:11 by amarchal          #+#    #+#             */
/*   Updated: 2022/04/29 17:09:45 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*buff;
	size_t	i;

	i = count * size;
	buff = malloc(sizeof(char) * i);
	if (!buff)
		exit(EXIT_FAILURE);
	ft_bzero(buff, i);
	return (buff);
}
