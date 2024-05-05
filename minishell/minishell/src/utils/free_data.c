/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:43:44 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/12 14:37:50 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	t_data is freed entirely except for the environment, which should survive
	until the program terminates.
*/
void	free_data(t_data *data)
{
	if (!data)
		return ;
	if (data->pid)
	{
		free(data->pid);
		data->pid = NULL;
	}
	if (data->input)
	{
		free(data->input);
		data->input = NULL;
	}
	if (data->tokens)
	{
		ft_lstclear(&data->tokens, del_tokens);
		data->tokens = NULL;
	}
	if (data->tree)
	{
		free_tree(data->tree);
		data->tree = NULL;
	}
	data->n_ps = -1;
}
