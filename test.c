#include "minishell.h"

int main1()
{
    // char *cmmd[] = "ls -l"; 
    int fd = open ("fike.txt", O_CREAT | O_RDWR, 0777);
    dup2(fd, 0);
    char *args[] = {"cat" , NULL};
    execve("/usr/bin/cat", args, NULL);
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	char *input;
	t_list	*args;
	t_list	*cmd;
	t_list	*current;
	t_info	*info;

	info = NULL;
	info = (t_info *)malloc(sizeof(t_info));
	args = NULL;
	cmd = NULL;
	input = NULL;
	
	fill_export_list(env, &info->head_ex);
	fill_env_list(env, &info->head_en);
	printf("\033[2J\033[1;1H");
	// print_list_env(env_list);
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
			ft_heredoc(args, &cmd);
			ft_rederection(args, &cmd);
			// t_cmd *cmd1 = cmd->data;
			choose_command(cmd, env, info);
			// 	(void)cmd1;
			// printf("[%s]\n", cmd1->cmds[0]);
			// printf("[%s]\n", cmd1->cmds[1]);
			// printf("[%d]\n", cmd1->fd_out);
			// printf("+-----------------------------+\n");
			// cmd = cmd->next;
			// if (cmd)
			// 	cmd1 = cmd->data;
			// printf("[%s]\n", cmd1->cmds[0]);
			// printf("[%s]\n", cmd1->cmds[1]);
			// printf("[%d]\n", cmd1->fd_out);
			// printf("+-----------------------------+\n");
			// cmd = cmd->next;
			// if (cmd)
			// 	cmd1 = cmd->data;
			// printf("[%s]\n", cmd1->cmds[0]);
			// printf("[%s]\n", cmd1->cmds[1]);
			// printf("[%d]\n", cmd1->fd_out);
			current = args;
			// // current1 = cmd;
			printf("+-----------------------------+\n");
			printf("| %4s            %s        |\n", "WORD", "TYPE");
			// printf("Adrr %p\n", cmd);
			while (current)
			{
				printf("|-----------------------------|\n");
				printf("| [%s]          [%d]         |\n", ((t_token *)(current->data))->value, ((t_token *)(current->data))->key);
				current = current->next;
			}
				printf("+---------------------------------+\n");
			// printf("+------------------------------+\n");
			// printf("|  %5s |  %5s  |   %5s   |\n",  "cmds", "fd_out", "fd_in");
			// int	i = 0;
			// while (cmd)
			// {
			// 	cmd1 = cmd->data;
			// 	printf("|-----------------------------|\n");
			// 	while (cmd1->cmds[i])
			// 		printf("|    %2s  |   %2d    |   %2d  |\n", cmd1->cmds[i++], cmd1->fd_out, cmd1->fd_in);
			// 	cmd = cmd->next;
			// }
			// 	printf("+----------------------------+\n");
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
