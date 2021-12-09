/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nlist_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ericlazo <erlazo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 19:38:06 by ericlazo          #+#    #+#             */
/*   Updated: 2021/12/09 14:46:53 by erlazo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilib.h"

int	ft_nlstadd_back(t_nlist **lst, t_nlist *new)
{
	size_t	i;
	t_nlist	*tmp;

	i = 0;
	if (!lst || !new)
	{
		return (0);
	}
	if (!*lst)
	{
		*lst = new;
		new->index = i;
		return (1);
	}
	tmp = *lst;
	while (tmp->next)
	{
		tmp = tmp->next;
		++i;
	}
	tmp->next = new;
	new->index = ++i;
	new->next = NULL;
	return (1);
}

int	ft_nlstadd_front(t_nlist **lst, t_nlist *new)
{
	if (!lst || !new)
	{
		if (new)
			free(new);
		return (0);
	}
	new->next = *lst;
	*lst = new;
	return (1);
}

t_nlist	*ft_nlstnew(void *content, int index)
{
	t_nlist	*elem;

	elem = (t_nlist *)malloc(sizeof(t_nlist));
	if (!elem)
		return (NULL);
	if (!content)
		elem->content = NULL;
	else
		elem->content = content;
	elem->index = index;
	elem->next = NULL;
	return (elem);
}

int	ft_nlstdel_all(t_nlist **lst)
{
	t_nlist	*tmp;

	if (!lst)
		return (0);
	tmp = *lst;
	while (*lst)
	{
		tmp = (*lst)->next;
		if ((*lst)->content)
			free((*lst)->content);
		free(*lst);
		*lst = tmp;
	}
	return (0);
}
