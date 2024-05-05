/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_a_token_node.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 13:02:54 by fahmadia          #+#    #+#             */
/*   Updated: 2023/11/06 12:04:26 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_next_node(t_list *cur_node)
{
	t_list	*temp;

	temp = cur_node->next->next;
	ft_lstdelone(cur_node->next, del_tokens);
	cur_node->next = temp;
}
