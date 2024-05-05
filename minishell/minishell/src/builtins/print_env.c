/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 15:16:10 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/07 09:40:49 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Outputs the environment variables which are at least an empty string. The
	uninitalized env var are not output like in the standar env builtin.
*/
int	print_env(t_list *env)
{
	t_var	*var;

	while (env)
	{
		var = (t_var *)env->content;
		if (var)
		{
			if (var->name && var->value)
			{
				ft_putstr_fd(var->name, 1);
				ft_putchar_fd('=', 1);
				ft_putendl_fd(var->value, 1);
			}
		}
		env = env->next;
	}
	return (0);
}
