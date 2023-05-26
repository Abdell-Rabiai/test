/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rederection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-nei <aben-nei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 01:21:27 by aben-nei          #+#    #+#             */
/*   Updated: 2023/05/18 16:32:12 by aben-nei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	fill_cmd(t_list **cmd, int fd_in, int fd_out, char *file_name, char **args)
{
	t_cmd	*cmds;

	cmds = NULL;
	// cmds->cmds = NULL;
	if (!*cmd)
	{
		cmds = (t_cmd *)malloc(sizeof(t_cmd));
		if (!cmds)
			return ;
		cmds->fd_in = fd_in;
		cmds->fd_out = fd_out;
		cmds->cmds = args;
		cmds->main_cmd = cmds->cmds[0];
		cmds->file_name = file_name;
		*cmd = ft_lstnew(cmds);
	}
	else
	{
		cmds = (t_cmd *)malloc(sizeof(t_cmd));
		if (!cmds)
			return ;
		cmds->fd_in = fd_in;
		cmds->fd_out = fd_out;
		cmds->cmds = args;
		cmds->main_cmd = cmds->cmds[0];
		cmds->file_name = file_name;
		ft_lstadd_back(cmd, ft_lstnew(cmds));
	}
}

void	rederection_app(t_list *args, int *fd_out)
{
	t_token	*token;

	token = args->data;
	if (token && token->key == RED_APP)
	{
		args = args->next;
		token = args->data;
		if (token && token->key == W_SPACE)
		{
			args = args->next;
			token = args->data;
		}
		if (token && token->key == RED_APP_FILE)
		{
			*fd_out = open(token->value, O_CREAT | O_RDWR | O_APPEND, 0777);
			args = args->next;
			if (args)
				token = args->data;
		}
	}
}

void	rederection_in(t_list *args, int *fd_in, char **file_name)
{
	t_token	*token;

	token = args->data;
	if (token && token->key == RED_INP)
	{
		args = args->next;
		token = args->data;
		if (token && token->key == W_SPACE)
		{
			args = args->next;
			token = args->data;
		}
		if (token && token->key == FILE_INP)
		{
			*fd_in = open(token->value, O_RDONLY);
			*file_name = token->value;
			// if (*fd_in < 0)
			// {
			// 	// printf("minishell: No such file or directory\n");
			// 	// printf("minishell: %s: No such file or directory\n", token->value);

			// 	return ;
			// }
			args = args->next;
			if (args)
				token = args->data;
		}
	}
}

void	rederection_out(t_list *args, int *fd_out)
{
	t_token	*token;

	token = args->data;
	if (token && token->key == RED_OUT)
	{
		args = args->next;
		token = args->data;
		if (token && token->key == W_SPACE)
		{
			args = args->next;
			token = args->data;
		}
		if (token && token->key == RED_FILE)
		{
			*fd_out = open(token->value, O_CREAT | O_RDWR, 0777);
			args = args->next;
			if (args)
				token = args->data;
		}
	}
}
