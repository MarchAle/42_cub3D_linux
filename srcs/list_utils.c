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

///////////// SPRITES

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

void	ft_lstfree_sprite(t_sprite *lst)
{
	t_sprite	*temp;

	while (lst)
	{
		temp = lst;
		lst = lst->next;
		temp = NULL;
		free(temp);
	}
	// lst = NULL;
	// free(lst);
}

///////////// DOORS

t_door	*ft_lstnew_door(int x, int y)
{
	static int id = 0;
	t_door	*newlist;

	newlist = malloc(sizeof(t_door));
	if (!newlist)
		return (NULL);
	newlist->id = id;
	id++;
	newlist->locked = 1;
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
	free(lst);
}

///////////// MONSTERS

t_monster	*ft_lstnew_monster(float x, float y)
{
	static int id = 0;
	t_monster	*newlist;

	newlist = malloc(sizeof(t_monster));
	if (!newlist)
		return (NULL);
	newlist->id = id;
	id++;
	newlist->health = 100;
	newlist->follow = 0;
	newlist->x = x + 0.5;
	newlist->y = y + 0.5;
	newlist->next = NULL;
	return (newlist);
}

void	ft_lstadd_back_monster(t_monster **alst, t_monster *new)
{
	t_monster	*last;

	if (!*alst)
		*alst = new;
	else
	{
		last = ft_lstlast_monster(*alst);
		last->next = new;
	}
}

t_monster	*ft_lstlast_monster(t_monster *lst)
{
	t_monster	*temp;
	t_monster	*actual;

	temp = lst;
	actual = lst;
	while (temp)
	{
		actual = temp;
		temp = temp->next;
	}
	return (actual);
}

void	ft_lstfree_monster(t_monster **lst)
{
	t_monster	*temp;

	temp = *lst;
	while (*lst)
	{
		*lst = temp->next;
		free(temp);
		temp = *lst;
	}
	free(lst);
}

///////////// KEYS

t_key	*ft_lstnew_key(float x, float y)
{
	static int id = 0;
	t_key	*newlist;

	newlist = malloc(sizeof(t_key));
	if (!newlist)
		return (NULL);
	newlist->id = id;
	id++;
	newlist->taken = 0;
	newlist->x = x + 0.5;
	newlist->y = y + 0.5;
	newlist->next = NULL;
	return (newlist);
}

void	ft_lstadd_back_key(t_key **alst, t_key *new)
{
	t_key	*last;

	if (!*alst)
		*alst = new;
	else
	{
		last = ft_lstlast_key(*alst);
		last->next = new;
	}
}

t_key	*ft_lstlast_key(t_key *lst)
{
	t_key	*temp;
	t_key	*actual;

	temp = lst;
	actual = lst;
	while (temp)
	{
		actual = temp;
		temp = temp->next;
	}
	return (actual);
}

void	ft_lstfree_key(t_key **lst)
{
	t_key	*temp;

	temp = *lst;
	while (*lst)
	{
		*lst = temp->next;
		free(temp);
		temp = *lst;
	}
	free(lst);
}

///////////// POTIONS

t_potion	*ft_lstnew_potion(float x, float y)
{
	static int id = 0;
	t_potion	*newlist;

	newlist = malloc(sizeof(t_potion));
	if (!newlist)
		return (NULL);
	newlist->id = id;
	id++;
	newlist->taken = 0;
	newlist->x = x + 0.5;
	newlist->y = y + 0.5;
	newlist->next = NULL;
	return (newlist);
}

void	ft_lstadd_back_potion(t_potion **alst, t_potion *new)
{
	t_potion	*last;

	if (!*alst)
		*alst = new;
	else
	{
		last = ft_lstlast_potion(*alst);
		last->next = new;
	}
}

t_potion	*ft_lstlast_potion(t_potion *lst)
{
	t_potion	*temp;
	t_potion	*actual;

	temp = lst;
	actual = lst;
	while (temp)
	{
		actual = temp;
		temp = temp->next;
	}
	return (actual);
}

void	ft_lstfree_potion(t_potion **lst)
{
	t_potion	*temp;

	temp = *lst;
	while (*lst)
	{
		*lst = temp->next;
		free(temp);
		temp = *lst;
	}
	free(lst);
}