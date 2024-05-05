/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:06:46 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/13 11:36:44 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	bye_bye(t_data *data, int last_e_code)
{
	free_data(data);
	ft_lstclear(&data->env, del_var_content);
	rl_clear_history();
	exit(last_e_code);
}

static int	is_valid_number(char *s, t_list *tkns)
{
	int			n;
	size_t		i;
	t_tkn_data	*tkn_cont;

	tkn_cont = (t_tkn_data *)tkns->next->content;
	if (tkn_cont->str[0] == '\'' || tkn_cont->str[0] == '\"')
		return (0);
	n = ft_atoi(s);
	i = 0;
	if (!n)
	{
		while (s[i] == '0')
			i++;
		if (i != ft_strlen(s))
			return (0);
	}
	return (1);
}

int	exit_custom(t_cmd *cmd, t_data *data)
{
	int		n;

	n = 0;
	ft_putendl_fd("exit", 1);
	while (cmd->args[n])
		n++;
	if (n == 1)
		bye_bye(data, data->e_code);
	else
	{
		if (!is_valid_number(cmd->args[1], data->tokens))
		{
			error("exit", cmd->args[1], CE_NUM_REQUIRED);
			bye_bye(data, 255);
		}
		else
		{
			if (n == 2)
				bye_bye(data, ft_atoi(cmd->args[1]) % 256);
			else
				error("exit", cmd->args[1], CE_TOOMANYARGS);
		}
	}
	return (1);
}
