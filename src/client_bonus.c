/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssukhova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:47:19 by ssukhova          #+#    #+#             */
/*   Updated: 2024/03/22 15:36:15 by ssukhova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <limits.h>
#include <stdbool.h>
#include "libft.h"

static volatile sig_atomic_t	g_accepted;

void	handle_signal(int signal)
{
	if (signal == SIGUSR1)
		g_accepted = true;
}

void	send_byte(int pid, char byte)
{
	int		sig;
	int		i;
	char	mask;

	mask = 0b00000001;
	i = 0;
	while (i++ < CHAR_BIT)
	{
		if (byte & mask)
			sig = SIGUSR1;
		else
			sig = SIGUSR2;
		g_accepted = false;
		if (kill(pid, sig) == -1)
		{
			ft_printf("Error sending bit");
			exit(EXIT_FAILURE);
		}
		mask = mask << 1;
		while (!g_accepted)
			usleep(50);
	}
}

int	main(int argc, char **argv)
{
	int					pid;
	char				*message;
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = handle_signal;
	if (sigaction(SIGUSR1, &sa, NULL) != 0)
	{
		ft_printf("Error with sigaction");
		exit(EXIT_FAILURE);
	}
	if (argc != 3)
	{
		ft_printf("Usage: %s <Signal Number> <Server PID>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	pid = ft_atoi(argv[1]);
	message = argv[2];
	while (*message)
		send_byte(pid, *message++);
	send_byte(pid, '\0');
	ft_printf ("all the bits sent have been received by the server");
	return (0);
}
