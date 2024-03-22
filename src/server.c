/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssukhova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:23:25 by ssukhova          #+#    #+#             */
/*   Updated: 2024/03/21 16:35:39 by ssukhova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "libft.h"
#include "struct.h"

void	handle_signal(int signal, siginfo_t *info, void *ctx)
{
	static t_context	cont = {0};

	(void) ctx;
	if (cont.i != CHAR_BIT)
	{
		if (signal == SIGUSR1)
			cont.c = (cont.c >> 1) | 0b10000000;
		else if (signal == SIGUSR2)
			cont.c = cont.c >> 1;
		cont.i++;
		if (cont.i == CHAR_BIT)
		{
			if (cont.c == '\0')
				cont.c = '\n';
			write(1, &cont.c, 1);
			cont.i = 0;
			cont.c = 0;
		}
		if (kill(info->si_pid, SIGUSR1) == -1)
		{
			ft_printf("Error sending acc");
			exit(EXIT_FAILURE);
		}
	}
}

int	main(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	sa.sa_sigaction = &handle_signal;
	if (sigaction(SIGUSR1, &sa, NULL) != 0)
	{
		ft_printf("Error with sigaction");
		exit(EXIT_FAILURE);
	}
	if (sigaction(SIGUSR2, &sa, NULL) != 0)
	{
		ft_printf("Error with sigaction");
		exit(EXIT_FAILURE);
	}
	ft_printf("Server PID: %d\n", getpid());
	while (1)
		pause();
	return (0);
}
