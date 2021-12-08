/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_main_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <erlazo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 03:33:41 by me                #+#    #+#             */
/*   Updated: 2021/12/08 08:52:44 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_sigusr_handler()
{
	ft_putstr("Message Received!\n");
}

int	ft_send_bit(char c, int pid)
{
	int	i;

	i = 0;
//	printf("sending bit: %c\n", c);
	while (i < 8)
	{
//		printf("in the send bit loop\n");
		if (c & 1<<i)
		{
			if ((kill(pid, SIGUSR1)) == -1)
				return (ft_error_msg_fd("Error, bad PID\n", 0, 0));
		}
		else
		{
			if ((kill(pid, SIGUSR2)) == -1)
				return (ft_error_msg_fd("Error, bad PID\n", 0, 0));
		}
		usleep(100);
		++i;
	}
	return (1);
}




	// make a thing useing FORK or something where you can test if
	// the server is able to handle multiple clients sending parts of
	// messages all at the same time
	// i think it is, but make a thing to prove it, if only for the correction



int	main(int ac, char **av)
{
	int		i;
	int		j;
	int		pid;
	int		cpid;
	struct sigaction	sa;

	cpid = -1;
	if (ac < 3 || ac > 4)
		return (ft_error_msg_fd("Error, expected arguments: <PID> <Message>\n", 0, 0));
	if (!ft_str_isdigit(av[1]))
		return (ft_error_msg_fd("Error, PID must be a number\n", 0, 0));
	if (!ft_str_isprint(av[2]))
		return (ft_error_msg_fd("Error, Message is not fully printable.\n", 0, 0));
	if (ac == 4)
	{
		cpid = fork();
		if (!ft_str_isprint(av[3]))
			return (ft_error_msg_fd("Error, 2nd Message is not fully printable.\n", 0, 0));
		printf("bonuse client fork child pid: %d\n", cpid);
	}
	pid = ft_atoi(av[1]);

	sa.sa_handler = &ft_sigusr_handler;
	sigaction(SIGUSR1, &sa, NULL);

	if (!ft_strcmp(av[2], "kill server"))
	{
		ft_putstr("Killing Server\n");
		kill(pid, SIGINT);
	}
	int	ret;

	ret =1;
	i = 0;
	j = 0;
	//while (av[2][i])

	if (!cpid)
	{
		// child process
		usleep(200);
		while (av[3][i])
		{
			if (!ft_send_bit(av[3][i], pid))
				return (0);
			++i;
			usleep(200);
		}
		ft_send_bit('\0', pid);
	}
	else
	{
		// parent process
		while (av[2][i])
		{
			if (!ft_send_bit(av[2][i], pid))
				return (0);
			++i;
			usleep(200);
		}
		ft_send_bit('\0', pid);
	}



/*
	while (ret)
	{
//		printf("main sending bits loop\n");
		ret = 0;
		if (!cpid)
		{
			if (!ft_send_bit(av[3][j], pid))
				return (0);
			++j;
			ret = 1;
		}
		else
		{
			if (!ft_send_bit(av[2][i], pid))
				return (0);
			++i;
		}
		if (!av[2][i] || !av[3][j])
			ft_send_bit('\0', pid);

	}
*/
	//ft_send_bit('\0', pid);
	return (0);
}
