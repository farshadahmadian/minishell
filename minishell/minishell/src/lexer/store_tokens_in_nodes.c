/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_tokens_in_nodes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:01:53 by fahmadia          #+#    #+#             */
/*   Updated: 2023/11/21 07:33:13 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_tkn_data(t_list *tkn_node, char *tkn_str, t_list **tkn_head)
{
	t_tkn_data	*tkn_data;
	t_tkn_data	*tkn_head_data;
	size_t		str_len;

	str_len = ft_strlen(tkn_str);
	tkn_data = malloc(1 * sizeof(t_tkn_data));
	tkn_node->content = tkn_data;
	tkn_head_data = ((t_tkn_data *)(*tkn_head)->content);
	tkn_data->str = tkn_str;
	if (tkn_node == *tkn_head)
	{
		tkn_data->list_size = 1;
		tkn_head_data->list_size = 1;
	}
	else
		tkn_head_data->list_size++;
	tkn_data->list_size = tkn_head_data->list_size;
	tkn_data->type = 0;
	tkn_data->quote = 0;
	tkn_data->str_len = str_len;
	tkn_data->quote_status = NO_QUOTE;
	tkn_data->white_space = INIT_WHITE_SPACE;
}

char	*store_special_char_as_tkn(char *c, t_list **tkn_head)
{
	char	*special_char_str;
	t_list	*special_char_node;

	special_char_str = malloc((1 + 1) * sizeof(char));
	if (!special_char_str)
		return (NULL);
	special_char_str[1] = '\0';
	special_char_node = malloc(1 * sizeof(t_list));
	if (!special_char_node)
		return (NULL);
	special_char_node->content = NULL;
	special_char_node->next = NULL;
	ft_memset(special_char_str, *c, 1);
	ft_lstadd_back(tkn_head, special_char_node);
	init_tkn_data(special_char_node, special_char_str, tkn_head);
	return (special_char_str);
}

char	*store_prev_chars_as_tkn(char *ref, int tkn_counter, t_list **tkn_head)
{
	char	*last_tkn_str;
	t_list	*last_tkn_node;

	if (tkn_counter < 2)
		return (NULL);
	last_tkn_str = malloc((tkn_counter) * sizeof(char));
	if (!last_tkn_str)
		return (NULL);
	last_tkn_str[tkn_counter - 1] = '\0';
	last_tkn_node = malloc(1 * sizeof(t_list));
	if (!last_tkn_node)
		return (NULL);
	last_tkn_node->content = NULL;
	last_tkn_node->next = NULL;
	ft_strlcpy(last_tkn_str, ref, tkn_counter);
	ft_lstadd_back(tkn_head, last_tkn_node);
	init_tkn_data(last_tkn_node, last_tkn_str, tkn_head);
	return (last_tkn_str);
}
