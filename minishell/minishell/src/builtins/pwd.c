/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 10:52:18 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/09 13:57:29 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	pwd command returns the current working path. The function getcwd()
	allocates memory that should be freed.
*/
int	pwd(void)
{
	char	*buff;
	size_t	size;

	buff = NULL;
	size = 1;
	buff = getcwd(buff, size);
	while (!buff && errno == ERANGE)
	{
		size += 1;
		buff = getcwd(buff, size);
		if (!buff && errno != ERANGE)
			return (error("pwd", NULL, errno), 1);
	}
	ft_putendl_fd(buff, 1);
	free (buff);
	return (0);
}
