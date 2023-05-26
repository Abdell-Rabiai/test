/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 17:32:01 by aben-nei          #+#    #+#             */
/*   Updated: 2023/05/26 21:42:54 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"
// #include "../libft/libft.h"

void	print_list1(t_list *cmd)
{
	int i = 0;
	if (!cmd)
		return ;
	t_list *tmp = cmd;
	t_cmd *token = cmd->data;
	while (tmp)
	{
		token = tmp->data;
		i = 0;
		while (tmp && token->cmds[i])
		{
			printf("tmp[%d] = %s\n", i, token->cmds[i]);
			i++;
		}
		tmp = tmp->next;
	}
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	char *input;
	t_list	*args;
	t_list	*cmd;
	t_info	*info;

	info = NULL;
	info = (t_info *)malloc(sizeof(t_info));
	args = NULL;
	cmd = NULL;
	input = NULL;

	fill_export_list(env, &info->head_ex);
	fill_env_list(env, &info->head_en);
	printf("\033[2J\033[1;1H");
	while (42)
	{
		input = readline("-> minishell$ ");
		if (input)
		{
			add_history(input);
			if (check_quotes(input))
			{
				free(input);
				printf("minishell: quotes not closed\n");
        	    continue ;
			}
			get_token(input, &args);
			if (args && syntex_error(args))
			{
				ft_lstclear(&args);
				continue ;
			}
			ft_trim_quotes(&args);
			ft_expand(&args, info->head_en);
			ft_join_args(&args);
			command_table(args, &cmd);
			// t_cmd *token = cmd->data;
			// if (token->cmds[0])
			// {
			// 	printf("token = [%s]\n", token->cmds[0]);
			// 	printf("token = [%s]\n", token->cmds[1]);
			// }
			if (cmd)
				choose_command(cmd, info);
			ft_lstclear(&args);
			ft_lstclear(&cmd);
		}
		else
		{
			free(input);
			printf(" exit\n");
			break ;
    	}
		}
	return (0);
}
