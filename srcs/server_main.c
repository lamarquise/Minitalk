/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <erlazo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 03:34:55 by me                #+#    #+#             */
/*   Updated: 2021/12/10 09:19:12 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// REMOVE THIS!!!!!!!
int	thing = 0;

char	*ft_add_char_to_str(char c, char *str, t_nlist **lst, int pid)
{
	int		i;
	char	*ret;

	// remove!!!!
	++thing;

	if (thing > 9)
	{
		kill(pid, SIGUSR2);
		ft_nlstdel_all(lst);
	}
	i = 0;
	ret = malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (!ret)
	{
		kill(pid, SIGUSR2);
		ft_nlstdel_all(lst);
	}
	while (str && str[i])
	{
		ret[i] = str[i];
		++i;
	}
	ft_scott_free(&str, 0);
	ret[i] = c;
	++i;
	ret[i] = '\0';
	return (ret);
}

t_nlist	*ft_get_right_elem(t_nlist *lst, int pid)
{
	t_nlist	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (tmp->index == pid)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_nlist	*ft_right_elem(t_nlist **lst, int pid)
{
	t_nlist	*tmp;

	tmp = NULL;
	if (*lst)
	{
		tmp = ft_get_right_elem(*lst, pid);
		if (!tmp)
		{
			tmp = ft_nlstnew(NULL, pid);
			if (!ft_nlstadd_front(lst, tmp))
			{
				kill(pid, SIGUSR2);
				ft_nlstdel_all(lst);
			}
		}
	}
	else
	{
		tmp = ft_nlstnew(NULL, pid);
		if (!ft_nlstadd_front(lst, tmp))
		{
			kill(pid, SIGUSR2);
			ft_nlstdel_all(lst);
		}
	}
	return (tmp);
}

void	ft_sigusr_handler(int sig, siginfo_t *info, void *unused)
{
	static int		i = 0;
	static int		c = 0;
	static t_nlist	*lst = NULL;
	t_nlist			*tmp;

	(void)unused;
	tmp = ft_right_elem(&lst, info->si_pid);
	if (sig == SIGUSR1)
		c |= (1 << i);
	++i;
	if (i == 8 && tmp)
	{
		i = 0;
		if (!c)
		{
			ft_putstr(tmp->content);
			ft_putchar('\n');
			ft_nlstdel_n_one(&lst, info->si_pid);
			if ((kill(info->si_pid, SIGUSR1) == -1))
				ft_error_msg_fd("Failed to send signal back to client\n", 0, 0);
		}
		else
			tmp->content = ft_add_char_to_str(c, tmp->content, &lst, info->si_pid);
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
	while (1)
		pause();
	return (0);
}
