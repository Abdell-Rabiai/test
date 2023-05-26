/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-nei <aben-nei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 19:32:47 by aben-nei          #+#    #+#             */
/*   Updated: 2023/05/16 23:58:17 by aben-nei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	get_number_of_commands(t_list *args)
{
	int	i;

	i = 0;
	while (args)
	{
		if (((t_token *)(args->data))->key == PIPE)
			i++;
		args = args->next;
	}
	return (++i);
}

char	**get_command1(t_list *args)
{
	t_token	*token;
	char	**cmd;
	int		i;
	int		flag;
	int		number_of_commands;

	i = 0;
	flag = 0;
	cmd = NULL;
	number_of_commands = allocate_commande(args);
	cmd = (char **)malloc(sizeof(char *) * (number_of_commands + 1));
	if (!cmd)
		return (NULL);
	cmd[number_of_commands] = NULL;
	while (args)
	{
		token = args->data;
		if (token->key == RED_APP || token->key == RED_INP
			|| token->key == RED_OUT || token->key == HEREDOC
			|| token->key == RED_APP_FILE || token->key == RED_FILE
			|| token->key == FILE_INP || token->key == EOFILE)
			{
				flag++;
				args = args->next;
				if (!args)
					break ;
				token = args->data;
			}
		if (flag == 2)
			flag = 0;
		if (token->key == PIPE)
			break ;
		else if (token->key == W_SPACE)
		{
			args = args->next;
			if (!args)
				break ;
			token = args->data;
		}
		else if (token->key == WORD || token->key == FLAG
				|| token->key == SQUATES || token->key == DQUATES
				|| token->key == VAR)
		{
			if (!flag)
			{
				cmd[i++] = ft_strdup(token->value);
			}
			// free(token->value);
			args = args->next;
			if (!args)
				break ;
			token = args->data;
			flag = 0;
		}
		// else
		// 	args = args->next;
	}
	return (cmd);
}

void	ft_remove_node(t_list **head, t_list *node)
{
	t_list	*tmp;
	t_list	*next_node;

	tmp = *head;
	if (tmp == NULL)
		return ;
	if (tmp == node)
	{
		*head = tmp->next;
		free (tmp);
		return ;
	}
	while (tmp->next && tmp->next != node)
		tmp = tmp->next;
	if (tmp->next == NULL)
		return ;
	next_node = tmp->next->next;
	free(tmp->next);
	tmp->next = next_node;
}

void	ft_join_args(t_list **args)
{
	t_list	*tmp;
	t_token	*list;
	char	*token;

	tmp = *args;
	while (tmp && tmp->next != NULL)
	{
		token = NULL;
		list = tmp->data;
		if (list && list->key != W_SPACE && (list->key == SQUATES || list->key == DQUATES
			|| list->key == VAR || list->key == WORD || list->key == FLAG || list->key == RED_FILE
			|| list->key == FILE_INP || list->key == RED_APP_FILE || list->key == EOFILE))
			{
				token = list->value;
				if (tmp->next)
					list = tmp->next->data;
				if (list && list->key != W_SPACE && (list->key == SQUATES || list->key == DQUATES
					|| list->key == VAR || list->key == WORD || list->key == FLAG))
					{
						token = ft_strjoin(token, list->value);
						((t_token *)(tmp->data))->value = token;
							ft_remove_node(args, tmp->next);
						if (tmp)
							list = tmp->data;
					}
					else
						tmp = tmp->next;
			}
			else
				tmp = tmp->next;
	}
}
