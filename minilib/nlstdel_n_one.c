/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nlstdel_n_one.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ericlazo <erlazo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 20:36:48 by ericlazo          #+#    #+#             */
/*   Updated: 2021/12/09 08:02:47 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilib.h"

int	ft_nlstdel_n_one(t_nlist **lst, int n)
{
	t_nlist	*tmp;
	t_nlist	*prev;

	if (!lst || !*lst || n < 0)
		return (0);
	tmp = *lst;
	if (tmp && tmp->index == n)
	{
		prev = tmp->next;
		free(tmp->content);
		free(tmp);
		*lst = prev;
		return (1);
	}
	while (tmp && tmp->index != n)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (!tmp)
		return (0);
	prev->next = tmp->next;
	free(tmp->content);
	free(tmp);
	return (1);
}
