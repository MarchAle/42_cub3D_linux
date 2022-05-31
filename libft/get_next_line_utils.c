/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 13:41:20 by dvallien          #+#    #+#             */
/*   Updated: 2022/01/25 11:36:21 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

static void	ft_fill_tab_gnl(char *str, char *s1, char *s2, int len)
{
	int	i;

	i = 0;
	while (*s1)
		str[i++] = *s1++;
	while (*s2)
	{
		if (*s2 == '\n')
		{
			str[i++] = *s2++;
			break ;
		}
		str[i++] = *s2++;
	}
	str[i] = '\0';
	free(s1 - len);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*str;
	int		len_s1;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len_s1 = ft_strlen(s1);
	str = malloc(sizeof(char) * (ft_strlen((char *)s1)
				+ ft_strlen((char *)s2) + 1));
	if (!str)
		return (NULL);
	ft_fill_tab_gnl(str, s1, s2, len_s1);
	return (str);
}
