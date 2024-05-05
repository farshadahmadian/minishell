/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_to_pipes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 12:44:26 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/09 08:21:17 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	if (pipe), means that is a first or a middle child. In case pipe == NULL,
	means that is the last child of a pipechain.
*/
int	redirect_to_pipes(int *pipe, int *prev_pipe)
{
	int	fd_ret;

	fd_ret = -1;
	if (pipe)
	{
		fd_ret = dup2(pipe[1], STDOUT_FILENO);
		close(pipe[1]);
		fd_ret = dup2(*prev_pipe, STDIN_FILENO);
		close(pipe[0]);
		close(*prev_pipe);
	}
	else
	{
		fd_ret = dup2(*prev_pipe, STDIN_FILENO);
		close(*prev_pipe);
	}
	if (fd_ret == -1)
		return (error("dup2", NULL, errno), 1);
	return (0);
}
