/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_config.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 11:59:22 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/12 12:26:39 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Remove ^C when ctrl-c is pressed.
*/
void	terminal_config(void)
{
	struct termios	config;

	tcgetattr(0, &config);
	config.c_lflag &= ~ECHOCTL;
	tcsetattr(0, 0, &config);
}
