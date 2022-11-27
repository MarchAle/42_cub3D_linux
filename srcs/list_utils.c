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

t_sprite	*ft_lstnew_sprite(float x, float y, int type, float dist, float x_offset)
{
	t_sprite	*newlist;

	newlist = malloc(sizeof(t_sprite));
	if (!newlist)
		return (NULL);
	newlist->type = type;
	newlist->x = x;
	newlist->y = y;
	newlist->dist = dist;
	newlist->x_offset = x_offset;
	newlist->previous = NULL;
	newlist->next = NULL;
	return (newlist);
}

void	ft_lstadd_back_sprite(t_sprite **alst, t_sprite *new)
{
	t_sprite	*last;

	if (!*alst)
		*alst = new;
	else
	{
		last = ft_lstlast_sprite(*alst);
		last->next = new;
        new->previous = last;
	}
}

t_sprite	*ft_lstlast_sprite(t_sprite *lst)
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

void	ft_lstfree_sprite(t_sprite **lst)
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

t_door	*ft_lstnew_door(int x, int y)
{
	static int id = 0;
	t_door	*newlist;

	newlist = malloc(sizeof(t_door));
	if (!newlist)
		return (NULL);
	newlist->id = id;
	id++;
	newlist->x = x;
	newlist->x_min = x + 0.5 - DOOR_DIST;
	newlist->x_max = x + 0.5 + DOOR_DIST;
	newlist->y = y;
	newlist->y_min = y + 0.5 - DOOR_DIST;
	newlist->y_max = y + 0.5 + DOOR_DIST;
	newlist->near_player = 0;
	newlist->animation = 0;
	newlist->opening = 0;
	newlist->next = NULL;
	return (newlist);
}

void	ft_lstadd_back_door(t_door **alst, t_door *new)
{
	t_door	*last;

	if (!*alst)
		*alst = new;
	else
	{
		last = ft_lstlast_door(*alst);
		last->next = new;
	}
}

t_door	*ft_lstlast_door(t_door *lst)
{
	t_door	*temp;
	t_door	*actual;

	temp = lst;
	actual = lst;
	while (temp)
	{
		actual = temp;
		temp = temp->next;
	}
	return (actual);
}

void	ft_lstfree_door(t_door **lst)
{
	t_door	*temp;

	temp = *lst;
	while (*lst)
	{
		*lst = temp->next;
		free(temp);
		temp = *lst;
	}
}