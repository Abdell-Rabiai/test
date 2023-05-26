/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntex_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-nei <aben-nei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 08:47:32 by aben-nei          #+#    #+#             */
/*   Updated: 2023/05/17 21:02:04 by aben-nei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	syntex_error(t_list *list)
{
	int	flag;

	flag = 0;
	while (list)
	{
		if (list && ((t_token *)(list->data))->key == PIPE && !flag)
		{
			printf("minishell: syntax error near unexpected token `|'\n");
			return (1);
		}
		else if (((t_token *)(list->data))->key == HEREDOC || ((t_token *)(list->data))->key == RED_OUT
			|| ((t_token *)(list->data))->key == RED_APP || ((t_token *)(list->data))->key == RED_INP)
			{
				list = list->next;
				while (list && ((t_token *)(list->data))->key == W_SPACE)
					list = list->next;
				if (!list)
				{
					printf("minishell: syntax error near unexpected token `newline'\n");
					return (1);
				}
				if (list && ((t_token *)(list->data))->key == PIPE)
				{
					printf("minishell: syntax error near unexpected token `%s'\n", ((t_token *)(list->data))->value);
					return (1);
				}
				if (list && ((t_token *)(list->data))->key != EOFILE && ((t_token *)(list->data))->key != RED_APP_FILE
				&& ((t_token *)(list->data))->key!= FILE_INP && ((t_token *)(list->data))->key != RED_FILE
				&& ((t_token *)(list->data))->key != SQUATES && ((t_token *)(list->data))->key != DQUATES
				&& ((t_token *)(list->data))->key != VAR)
				{
					// printf("%d_______________'\n", ((t_token *)(list->data))->key);
					printf("minishell: syntax error near unexpected token2 `%s'\n", ((t_token *)(list->data))->value);
					return (1);
				}
				flag = 1;
			}
		else if (list && ((t_token *)(list->data))->key == PIPE && ((t_token *)(list->data))->flag_quote == 0)
		{
			list = list->next;
			while (list && ((t_token *)(list->data))->key == W_SPACE)
				list = list->next;
			if (!list || ((t_token *)(list->data))->key == PIPE)
			{
				printf("minishell: syntax error near unexpected token `|'\n");
                return (1);
			}
			else
				continue ;
			flag = 1;
		}
		// else if (list && ((t_token *)(list->data))->key == SYMBOLE)
		// {
		// 	printf("minishell: syntax error near unexpected token `%s'\n", ((t_token *)(list->data))->value);
		// 	return (1);
		// }
			else
				flag = 1;
		list = list->next;
	}
	return (0);
}
