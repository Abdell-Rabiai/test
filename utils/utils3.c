/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:15:49 by ahaloui           #+#    #+#             */
/*   Updated: 2023/05/26 22:29:09 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void execute_commands_with_pipe(t_list *cmd, t_info *info)
{
	int pipefd[2];
	pid_t pid1;
	int i;
	int nb_cmds;
	t_cmd *commands;

	i = 0;
	nb_cmds = ft_lstsize(cmd);
	commands = cmd->data;
	while (i < nb_cmds)
	{
		if (i < nb_cmds - 1)
		{
			if (pipe(pipefd) == -1)
			{
				ft_putstr_fd("Error: pipe failed\n", 2);
				exit(1);
			}
		}
		pid1 = fork();
		if (pid1 == -1)
		{
			printf("Error: fork failed\n");
			exit(1);
		}
		else if (pid1 == 0)
		{
			if (i == 0)
			{
				if (commands->fd_in != -1)
				{
					dup2(commands->fd_in, 0);
					close(commands->fd_in);
				}
				else
				{
					printf("minishell: %s: No such file or directory\n", commands->file_name);
					exit(EXIT_FAILURE);
				}
				if (commands->fd_out != 1)
				{
					dup2(commands->fd_out, 1);
					close(commands->fd_out);
				}
				else
				{
					close(pipefd[0]);
					dup2(pipefd[1], STDOUT_FILENO);
				}
				
				if (is_builin(commands) == 1)
				{
					builtin_execution(cmd, info, 0);
					exit(EXIT_SUCCESS);
				}
				else
					execve(check_if_command_found(commands->main_cmd, &info->head_ex), (commands->cmds), NULL);
			}
			else if (i == nb_cmds - 1)
			{
				if (commands->fd_in != -1)
					dup2(commands->fd_in, 0);
				else
				{
					printf("minishell: %s: No such file or directory\n", commands->file_name);
					exit(EXIT_FAILURE);
				}
				if (commands->fd_out != 1)
				{
					dup2(commands->fd_out, 1);
					close(commands->fd_out);
				}
				else
					dup2(info->out, 1);
					
				if (is_builin(commands) == 1)
					builtin_execution(cmd, info, 0);
				else
					execve(check_if_command_found(commands->main_cmd, &info->head_ex), (commands->cmds), NULL);
			}
			else
			{
				if (commands->fd_in != -1)
					dup2(commands->fd_in, 0);
				else
				{
					printf("minishell: %s: No such file or directory\n", commands->file_name);
					exit(EXIT_FAILURE);
				}
				if (commands->fd_out != 1)
				{
					dup2(commands->fd_out, 1);
					close(commands->fd_out);
				}
				else
				{
					dup2(pipefd[1], STDOUT_FILENO);
					close(pipefd[0]);
				}
				if (is_builin(commands) == 1)
					builtin_execution(cmd, info, 0);
				else
					execve(check_if_command_found(commands->main_cmd, &info->head_ex), (commands->cmds), NULL);
			}
		}
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[1]);
		i++;
		cmd = cmd->next;
		if (cmd)
			commands = cmd->data;
	}
	close(pipefd[1]);
	close(pipefd[0]);
	while (wait(NULL) != -1){}
}