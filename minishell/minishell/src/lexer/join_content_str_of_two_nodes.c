/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_content_str_of_two_nodes.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 12:40:11 by fahmadia          #+#    #+#             */
/*   Updated: 2023/11/13 09:35:11 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_two_strs(char **cur_str, char *next_str)
{
	char	*temp;

	temp = *cur_str;
	*cur_str = ft_strjoin(*cur_str, next_str);
	free(temp);
	return (*cur_str);
}
