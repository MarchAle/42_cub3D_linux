/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 14:44:55 by amarchal          #+#    #+#             */
/*   Updated: 2021/11/11 16:03:52 by amarchal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_sprite	*ft_lstnew(float x, float y)
{
	t_sprite	*newlist;

	newlist = malloc(sizeof(t_sprite));
	if (!newlist)
		return (NULL);
	newlist->x = x;
	newlist->y = y;
	newlist->previous = NULL;
	newlist->next = NULL;
	return (newlist);
}

void	ft_lstadd_back(t_sprite **alst, t_sprite *new)
{
	t_sprite	*last;

	if (!*alst)
		*alst = new;
	else
	{
		last = ft_lstlast(*alst);
		last->next = new;
        new->previous = last;
	}
}

t_sprite	*ft_lstlast(t_sprite *lst)
{
	t_sprite	*temp;
	t_sprite	*actual;

	temp = lst;
	actual = lst;
	while (temp)
	{
		actual = temp;
		temp = temp->next;
	}
	return (actual);
}

void	ft_lstfree(t_sprite **lst)
{
	t_sprite	*temp;

	temp = *lst;
	while (*lst)
	{
		*lst = temp->next;
		free(temp);
		temp = *lst;
	}
}