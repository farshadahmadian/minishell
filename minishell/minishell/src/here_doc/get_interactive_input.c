/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_interactive_input.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 10:39:26 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/13 11:36:17 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	@param data: data is passed only in case the expansion has to be performed.
	Otherwise NULL is passed, and expansion is skipped.
*/
static int	write_into_tmp_file(int fd_tmp, char *eof, t_data *data)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, eof) == 0)
			break ;
		else
		{
			if (data && ft_strchr(line, '$'))
			{
				line = expand(line, data);
				if (!line)
					return (error("here_doc", "expand", CE_HERE_DOC), 1);
			}
			ft_putendl_fd(line, fd_tmp);
			if (line)
				free(line);
		}
	}
	if (line)
		free(line);
	return (0);
}

/*
	The here_doc behaves differently if EOF is enclosed or not in quotes. If
	it contains quotes, the environment var and $? are not expanded; if EOF
	has no quote, they are expanded. That because, in case of here-doc, the
	quotes are removed only here.
*/
int	get_interactive_input(int fd_tmp, char **eof, t_data *data)
{
	char	*tmp;

	tmp = NULL;
	if (ft_strchr(*eof, TKN_S_QUOTE) || ft_strchr(*eof, TKN_D_QUOTE))
	{
		tmp = *eof;
		*eof = remove_quote_pairs(*eof);
		free(tmp);
		if (!*eof)
			return (1);
		if (write_into_tmp_file(fd_tmp, *eof, NULL))
			return (1);
	}
	else
	{
		if (write_into_tmp_file(fd_tmp, *eof, data))
			return (1);
	}
	return (0);
}
