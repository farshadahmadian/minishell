/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_each_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:06:18 by fahmadia          #+#    #+#             */
/*   Updated: 2023/10/26 15:29:10 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*check_is_special_char(char c)
{
	char	*result;
	char	*special_chars;

	special_chars = ">< \t\n\'\"\\|$";
	result = ft_strchr(special_chars, c);
	return (result);
}

void	read_char(char cur_char, char **ref, int *tkn_ctr, t_list **tkn_head)
{
	if (check_is_special_char(cur_char))
	{
		if (*tkn_ctr > 1)
		{
			store_prev_chars_as_tkn(*ref, *tkn_ctr, tkn_head);
			*ref += *tkn_ctr - 1;
			store_special_char_as_tkn(*ref, tkn_head);
			(*ref)++;
			*tkn_ctr = 0;
		}
		else
		{
			store_special_char_as_tkn(*ref, tkn_head);
			(*ref)++;
			*tkn_ctr = 0;
		}
	}
}
