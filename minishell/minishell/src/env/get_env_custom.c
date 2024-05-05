/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_custom.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:53:39 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/07 11:36:32 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Re-implementation of get_env() function, which is needed to work with
	the custom environment. It doesn't allocate!!!
*/
char	*get_env_custom(char *name, t_list *env)
{
	t_var	*var;
	t_list	*head;

	head = env;
	if (head)
	{
		while (head)
		{
			var = (t_var *)head->content;
			if (ft_strcmp(var->name, name) == 0)
				return (var->value);
			head = head->next;
		}
	}
	return (NULL);
}
