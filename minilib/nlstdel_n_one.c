/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nlstdel_n_one.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ericlazo <erlazo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 20:36:48 by ericlazo          #+#    #+#             */
/*   Updated: 2021/12/07 11:54:38 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilib.h"
#include <stdio.h> // DELETE THIS!!!!!!!

void	n_is_zero(t_nlist **lst)
{
	t_nlist	*tmp;

	tmp = (*lst)->next;
	free((*lst)->content);
	free(*lst);
	*lst = tmp;
}

	// also modified just for Minitalk

	// i need to handle the case where there is only 1 elem in list...
	// also if i need to delete just the 1st elem
int	ft_nlstdel_n_one(t_nlist **lst, int n)
{
	t_nlist	*tmp;
	t_nlist	*prev;

//	printf("at the start of nlstdel n one\n");
	if (!lst || !*lst || n < 0)
		return (0);
	prev = NULL;
	tmp = *lst;
	while (tmp && tmp->index != n) 
	{
//		printf("in nlstdel loop\n");
		prev = tmp;
		tmp = tmp->next;
	}
//	printf("post! loop of of nlstdel n one\n");
	// this is all very poorly thought out...
	// were is check if tmp exist? cuz do tmp->next!
	if (prev)
		prev->next = tmp->next;
	if (tmp)
	{
//		printf("nlstdel one in if there is tmp\n");
//		ft_scott_free(tmp->content, 0);
		if (tmp->content)
			free(tmp->content);
		free(tmp);
		tmp = NULL;
	}
	return (1);
}
