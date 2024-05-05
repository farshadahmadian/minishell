/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 09:56:58 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/07 13:50:45 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Take as argument a string without dollar sign included. It checks
	immediately if the parameter is $?, which is not an env var, but a Shell
	built-in variable.
*/
int	get_var_name_len(char *s)
{
	int	i;

	if (s[0] == '?')
		return (1);
	i = 0;
	while (s[i])
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (i);
		i++;
	}
	return (i);
}

int	get_n_dollars(char *s)
{
	int	n;

	n = 0;
	while (*s)
	{
		if (*s == '$')
			n++;
		s++;
	}
	return (n);
}
