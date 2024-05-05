/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 12:13:28 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/07 15:50:06 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_list *tokens)
{
	t_list		*temp;
	t_tkn_data	*tkn_data;

	temp = tokens;
	while (temp)
	{
		tkn_data = (t_tkn_data *)temp->content;
		ft_printf("%s • ", tkn_data->str);
		temp = temp->next;
	}
	ft_printf("\n");
}
