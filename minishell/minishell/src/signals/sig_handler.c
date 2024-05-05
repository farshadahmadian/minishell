/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:35:30 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/13 10:51:55 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_ctrl_c_pressed = 0;

/*
	SIGINT prints a new line.
	@line	rl_on_new_line() - tell the program to move to a new line
	@line	rl_redisplay() - update what is displayed, to reflect the buffer
*/
static void	new_line_and_redisplay(int sig_n)
{
	(void) sig_n;
	ft_putendl_fd("", STDOUT_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_ctrl_c_pressed = 1;
}

static void	new_line_no_redisplay(int sig_n)
{
	(void) sig_n;
	ft_putendl_fd("", STDOUT_FILENO);
	rl_on_new_line();
	g_ctrl_c_pressed = 1;
}

/*
	Used to catch ctrl+c when inputting into readline (either with an input
	or with a blank input).
*/
void	switch_g_var(t_data *data)
{
	if (g_ctrl_c_pressed)
	{
		data->e_code = 1;
		g_ctrl_c_pressed = 0;
	}
}

void	set_sig_action(int is_before_rl)
{
	struct sigaction	sa_quit;
	struct sigaction	sa_int;

	if (is_before_rl)
	{
		ft_bzero(&sa_quit, sizeof(sa_quit));
		ft_bzero(&sa_int, sizeof(sa_int));
		sa_quit.sa_handler = SIG_IGN;
		sa_quit.sa_flags = 0;
		sigaction(SIGQUIT, &sa_quit, NULL);
		sa_int.sa_flags = 0;
		sa_int.sa_handler = &new_line_and_redisplay;
		sigaction(SIGINT, &sa_int, NULL);
	}
	else
	{
		ft_bzero(&sa_int, sizeof(sa_int));
		sa_int.sa_flags = 0;
		sa_int.sa_handler = &new_line_no_redisplay;
		sigaction(SIGINT, &sa_int, NULL);
	}
}
