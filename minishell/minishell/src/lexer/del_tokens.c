/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:05:34 by fahmadia          #+#    #+#             */
/*   Updated: 2023/12/12 15:12:31 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_tokens(void *content)
{
	t_tkn_data	*token_data;

	token_data = (t_tkn_data *)content;
	if (!token_data)
		return ;
	if (token_data->str)
		free(token_data->str);
	free(token_data);
	token_data = NULL;
}
