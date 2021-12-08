/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <erlazo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 03:34:55 by me                #+#    #+#             */
/*   Updated: 2021/12/08 08:52:46 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// Maybe put this elsewhere...
int		ft_print_nlist(t_nlist *lst)
{
	t_nlist	*tmp;
	int i;

	if (!lst)
		return (0);
	i = 0;
	tmp = lst;
	while (tmp)
	{
		if (tmp->content)
			ft_putstr((char *)tmp->content);
		ft_putchar('\n');
		tmp = tmp->next;
		++i;
	}
	ft_putnbrnl(i);
	return (1);
}

char	*ft_add_char_to_str(char c, char *str)
{
	int		i;
	int		len;
	char	*ret;

	if (!str)
		len = 0;
	else
		len = ft_strlen(str);
//	printf("adding char to string, str: |%s|\n", str);
	i = 0;
	ret = NULL;
	ret = malloc(sizeof(char) * (len + 2));
	if (!ret)
		return (NULL);
	if (str)
	{
		while (str[i])
		{
			ret[i] = str[i];
			++i;
		}
		ft_scott_free(&str, 0);
	}
	ret[i] = c;
	++i;
	ret[i] = '\0';
	return (ret);
}

void	ft_sigusr_handler(int sig, siginfo_t *info, void *unused)
{
	static int	i = 0;
	static int	c = 0;
	static t_nlist	*lst = NULL;
	t_nlist		*tmp;

	(void)info;
	(void)unused;
	tmp = lst;

	printf("in server which cliend sent sig: %d\n", info->si_pid);
	if (tmp)
	{
//		printf("there is a thing in lst, pid: %d\n", tmp->index);
//		ft_print_nlist(lst);
	}
	else
//		printf("There is nto a thing in lst\n");

	while (tmp && tmp->index != info->si_pid)
	{
//		printf("in linked list loop\n");
//		ft_print_nlist(lst);
		tmp = tmp->next;
//		if (!tmp)
//			printf("end of the loop\n");
	}

	if (!tmp)
	{
		tmp = ft_nlstnew(NULL, info->si_pid);
		ft_nlstadd_front(&lst, tmp);
//		printf("just created tmp and added to list, tmp->'pid' %d\n", tmp->index);
	}
	if (sig == SIGUSR1)
		c |= (1 << i);
//	c |= (sig == SIGUSR2);
//	c <<= 1;
	++i;
	if (i == 8)
	{
//		printf("sigusr handler we made it to 8 bits\n");
		i = 0;
//		ft_putnbrnl(c);
//		ft_putchar(c);
		if (!c)
		{
//			printf("end of message, it should print: |%s|\n", (char*)tmp->content);
	// This could be a bonus...
			ft_putstr(tmp->content);
			ft_putchar('\n');
//			printf("end of message, pre del n one\n");
			ft_nlstdel_n_one(&lst, info->si_pid);	
//			printf("end of message, post! del n one\n");
			if ((kill(info->si_pid, SIGUSR1) == -1))
				ft_error_msg_fd("Error, could not send signal back to client\n", 0, 0);
//			if (lst)
//				printf("lst in handler print is still a thing!\n");
		}
		else
		{
			tmp->content = ft_add_char_to_str(c, tmp->content);
//			printf("we should have added conent... |%s|\n", (char*)tmp->content);
		}
//		if (lst)
//			printf("lst in handler is still a thing!\n");
		c = 0;
	}
}

int	main(int ac, char **av)
{
	struct sigaction	sa;

	if (ac != 1)
		return (ft_error_msg_fd("Error, there should be no arguments!\n", 0, 0));
	ft_putnbrnl(getpid());
	(void)av;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &ft_sigusr_handler;

	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);

//	sa.sa_handler = &ft_sigusr_handler;
//	sigaction(SIGUSR1, &sa, NULL);
/*
	sig1.sa_handler = &ft_sig1_handler;
	sigemptyset(&sig1.sa_mask);
	sigaddset(&sig1.sa_mask, SIGUSR1);
	sig2.sa_handler = &ft_sig2_handler;

	sigaction(SIGUSR1, &sig1, NULL);
	sigaction(SIGUSR2, &sig2, NULL);
*/

	while (1)
		pause();
	return (0);
}
