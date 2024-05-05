/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_spaces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:30:47 by fahmadia          #+#    #+#             */
/*   Updated: 2023/11/06 12:04:55 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*get_prev_node(t_list *tkns_head)
{
	t_tkn_data	*next_tkn_data;
	t_list		*temp;

	temp = tkns_head;
	while (temp && temp->next)
	{
		next_tkn_data = (t_tkn_data *)(temp->next->content);
		if ((*(next_tkn_data->str) == TKN_SPACE_CAHR
				|| *(next_tkn_data->str) == TKN_TAB_CHAR)
			&& next_tkn_data->quote == NOT_QUOTED)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

static void	del_space_node_as_first_tkn(t_list **tkns_head)
{
	t_list			*temp;
	t_tkn_data		*tkns_head_data;
	int				list_size;

	temp = *tkns_head;
	while (temp)
	{
		tkns_head_data = (t_tkn_data *)((*tkns_head)->content);
		if (((tkns_head_data->str)[0] == TKN_SPACE_CAHR
			|| *(tkns_head_data->str) == TKN_TAB_CHAR)
			&& tkns_head_data->quote == NOT_QUOTED)
		{
			list_size = ((t_tkn_data *)((*tkns_head)->content))->list_size - 1;
			*tkns_head = (*tkns_head)->next;
			ft_lstdelone(temp, del_tokens);
			temp = *tkns_head;
			if (*tkns_head)
				((t_tkn_data *)((*tkns_head)->content))->list_size = list_size;
			continue ;
		}
		else
			return ;
		temp = temp->next;
	}
}

static void	del_space_node_in_middle_or_end(t_list *tkns_head)
{
	t_list			*cur_node;
	t_list			*before_white_space;
	t_tkn_data		*cur_tkn_data;

	cur_node = tkns_head;
	while (cur_node)
	{
		cur_tkn_data = (t_tkn_data *)(cur_node->content);
		if ((*(cur_tkn_data->str) == TKN_SPACE_CAHR
				|| *(cur_tkn_data->str) == TKN_TAB_CHAR)
			&& cur_tkn_data->quote == NOT_QUOTED)
		{
			before_white_space = get_prev_node(tkns_head);
			remove_next_node(before_white_space);
			cur_node = before_white_space->next;
			((t_tkn_data *)((tkns_head)->content))->list_size--;
			continue ;
		}
		cur_node = cur_node->next;
	}
}

void	delete_not_quoted_spaces(t_list **tkns_head)
{
	del_space_node_as_first_tkn(tkns_head);
	del_space_node_in_middle_or_end(*tkns_head);
}
