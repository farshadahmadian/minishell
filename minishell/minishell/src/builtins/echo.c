/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 16:23:38 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/12 13:17:11 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Iterate through the tkn list, until the argument (i) is reached. Then the
	information hold by t_white_space is read, to understand if the token is
	follwed by white space or not.
*/
static int	needs_whitespace(t_list *tkn, int i)
{
	t_list	*head;
	int		j;

	head = tkn;
	j = 0;
	while (j != i)
	{
		j++;
		head = head->next;
		if (!head)
			return (0);
	}
	if (((t_tkn_data *)head->content)->white_space == FOLLOWED_BY_WHITE_SPACE)
		return (1);
	return (0);
}

/*
	echo writes any oprand to stdout separated by a single blank char, and
	followed by a new line. As the subject states, it has to be implemented
	with the optional -n argument.
	@param i: starting point from which print the argument. In case of option -n
	the first argument to be printed is the number 2.
*/
int	echo(t_data *data, t_cmd *cmd)
{
	int		i;
	int		new_line;

	new_line = 1;
	i = 1;
	while (cmd->args[i] && ft_strcmp(cmd->args[i], "-n") == 0)
	{
		new_line = 0;
		i++;
	}
	while (cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i], 1);
		if (needs_whitespace(data->tokens, i) && cmd->args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (new_line)
		ft_putchar_fd('\n', 1);
	return (0);
}
