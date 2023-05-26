/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-nei <aben-nei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 23:31:15 by aben-nei          #+#    #+#             */
/*   Updated: 2023/05/23 23:31:18 by aben-nei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	allocate_commande(t_list *args)
{
	t_token	*token;
	int	i;
	int flag;

	i = 0;
	flag = 0;
	while (args)
	{
		token = args->data;
		if (token->key == PIPE)
			break ;
		else if (token->key == RED_APP || token->key == RED_INP
			|| token->key == RED_OUT || token->key == HEREDOC)
			{
				flag = 1;
				args = args->next;
			}
		else if (token->key == W_SPACE)
		{
			args = args->next;
			token = args->data;
		}
		else if (token->key == WORD || token->key == FLAG
				|| token->key == SQUATES || token->key == DQUATES
				|| token->key == VAR)
		{
			if (!flag)
				i++;
			args = args->next;
			flag = 0;
		}
		else
		{
			args = args->next;
			flag = 0;
		}
	}
	return (i);
}

void	command_table(t_list *args, t_list **cmd)
{
	t_token	*token;
	t_list	*tmp;
	int		fd_in;
	int		fd_out;
	char	*file_name;

	tmp = args;
	while (args)
	{
		fd_in = 0;
		fd_out = 1;
		token = args->data;
		while (token && token->key != PIPE)
		{
			if (token && token->key == RED_OUT)
			{
				rederection_out(args, &fd_out);
				args = args->next;
				token = args->data;
			}
			else if (token && token->key == RED_INP)
			{
				rederection_in(args, &fd_in, &file_name);
				args = args->next;
				token = args->data;
			}
			else if (token && token->key == RED_APP)
			{
				rederection_app(args, &fd_out);
				args = args->next;
				token = args->data;
			}
			else if (token && token->key == HEREDOC)
			{
				ft_heredoc(args, cmd);
				args = args->next;
				token = args->data;
			}
			else
			{
				args = args->next;
				if (!args)
					break ;
				token = args->data;
			}
		}
		fill_cmd(cmd, fd_in, fd_out, file_name, get_command1(tmp));
		// printf("fd_in = %d\n", fd_in);
		// printf("fd_out = %d\n", fd_out);
		if (token && token->key == PIPE)
		{
			args = args->next;
			token = args->data;
			tmp = args;
		}
	}
}
