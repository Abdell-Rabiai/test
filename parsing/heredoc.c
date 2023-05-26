/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-nei <aben-nei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:17:08 by aben-nei          #+#    #+#             */
/*   Updated: 2023/05/02 15:40:57 by aben-nei         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../include/minishell.h"

// function to print the list of cmds for debugging
// void	print_list(t_list *list)
// {
// 	t_cmd *token;

// 	while (list)
// 	{
// 		token = list->data;
// 		printf("key: %s, value: %s\n", token->cmds[0], token->cmds[1]);
// 		list = list->next;
// 	}
// }

// function to print the list
void	print_list(t_list *list)
{
	t_token *token;

	while (list)
	{
		token = list->data;
		printf("key: %d, value: %s\n", token->key, token->value);
		list = list->next;
	}
}

char *generate_name()
{
	static int i = 0;
	char *name;
	char *num;

	name = ft_strdup("/tmp/outfile");
	num = ft_itoa(i);
	name = ft_strjoin(name, num);
	name = ft_strjoin(name, ".txt");
	i++;
	return (name);
}

void    ft_heredoc(t_list *args, t_list **cmd)
{
	char *input;
	t_cmd *cmd_list = malloc(sizeof(t_cmd));
	// int	fd;
	char *name;

	while (args)
	{
		if (args->data && ((t_token *)(args->data))->key == HEREDOC)
		{
			cmd_list = args->data;
			((t_token *)(args->data))->key = RED_INP;
			((t_token *)(args->data))->value = ft_strdup("<");
			// printf("%s\n", ((t_token *)(args->data))->value);
			args = args->next;
			ft_remove_node(&args, args->data);
			if (args && ((t_token *)(args->data))->key == W_SPACE)
				args = args->next;
			name = generate_name();
			cmd_list->fd_in = open(name, O_CREAT | O_RDWR | O_TRUNC, 0777);
			if (cmd_list->fd_in == -1)
				perror("open ");
		while ((input = readline("HEREDOC$ ")) != NULL)
		{
			if (args && !ft_strncmp(input, ((t_token *)(args->data))->value))
			{
				// printf("Before remove\n");
				// print_list(args);
				// ft_remove_node(&args, args->data);
				// printf("After remove\n");
				// print_list(args);
				// printf("_________________\n");
				((t_token *)(args->data))->key = FILE_INP;
				((t_token *)(args->data))->value = name;
				// printf("%s\n", ((t_token *)(args->data))->value);
				// free(input);
				break;
			}
			ft_putstr_fd(input, cmd_list->fd_in);
			write(cmd_list->fd_in, "\n", 1);
		}
		(void)cmd;
		// fill_cmd(cmd, cmd_list->fd_in, cmd_list->fd_out, get_command(args));
	}
	else
		args = args->next;
	}
	
}