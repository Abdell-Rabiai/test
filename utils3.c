/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:15:49 by ahaloui           #+#    #+#             */
/*   Updated: 2023/05/11 21:20:25 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int number_of_commands(char **split)
{
    int i = 0;
    int num_commands = 0;
    while (split[i])
    {
        if (!ft_strcmp(split[i], "|"))
            num_commands++;
        i++;
    }
    return num_commands + 1;
}

// int execute_command_with_pipe(char **split, char **environ, t_env **head_en, t_export **head_ex) {
    
    
//     int pipefd[2];
//     pid_t pid;
    
//     // Create pipe
//     if (pipe(pipefd) == -1) {
//         perror("pipe");
//         exit(EXIT_FAILURE);
//     }
    
//     // Create child process
//     pid = fork();
//     if (pid == -1) {
//         perror("fork");
//         exit(EXIT_FAILURE);
//     }
    
//     if (pid == 0) { // Child process
//         // Close unused read end of pipe
//         close(pipefd[READ_END]);
        
//         // Redirect stdout to write end of pipe
//         if (dup2(pipefd[WRITE_END], STDOUT_FILENO) == -1) {
//             perror("dup2");
//             exit(EXIT_FAILURE);
//         }
        
//         // Execute command1
//         char *args[] = command1;
//         execvp(args[0], args);
        
//         // Execution should not reach here unless there is an error
//         perror("execvp");
//         exit(EXIT_FAILURE);
//     }
    
//     // Parent process
//     // Close unused write end of pipe
//     close(pipefd[WRITE_END]);
    
//     // Redirect stdin to read end of pipe
//     if (dup2(pipefd[READ_END], STDIN_FILENO) == -1) {
//         perror("dup2");
//         exit(EXIT_FAILURE);
//     }
    
//     // Execute command2
//     char *args[] = {split[0], split[1], NULL};
//     execvp(args[0], args);
    
//     // Execution should not reach here unless there is an error
//     perror("execvp");
//     exit(EXIT_FAILURE);
// }


// // void execute_command_with_pipe(char **split, char **environ, t_env **head_en, t_export **head_ex)
// // {
// //     // printf("execute_command_with_pipe\n");
// //     (void)environ;
// //     (void)head_en;
// //     (void)head_ex;
// //     (void)split;
    
// //     int i = 0;
// //     int num_commands = number_of_commands(split);
// //     int pipes[num_commands - 1][2];

// //     printf("num_commands = %d\n", num_commands);
// //     while (i < num_commands - 1)
// //     {
// //         if (pipe(pipes[i]) == -1) 
// //         {
// //             perror("pipe");
// //             exit(EXIT_FAILURE);
// //         }
// //         i++;
// //     }
// //     i = 0;
// //     int in_fd = STDIN_FILENO;
// //     // int out_fd;
// //     while (i < num_commands) 
// //     {
// //         pid_t pid = fork();
        
// //         if (pid == -1) 
// //         {
// //             perror("fork");
// //             exit(EXIT_FAILURE);
// //         }
// //         if (pid == 0) 
// //         { 
// //             // Child process
// //             if (i < num_commands - 1) 
// //             {
// //                 if (dup2(pipes[i][WRITE_END], STDOUT_FILENO) == -1) {
// //                     perror("dup2");
// //                     exit(EXIT_FAILURE);
// //                 }
// //             }

// //             if (i > 0) 
// //             { 
// //                 // Not the first command
// //                 if (dup2(in_fd, STDIN_FILENO) == -1) 
// //                 {
// //                     perror("dup2");
// //                     exit(EXIT_FAILURE);
// //                 }
// //             }
// //             int j = 0;
// //             while (j < num_commands - 1)
// //             {
// //                 close(pipes[j][READ_END]);
// //                 close(pipes[j][WRITE_END]);
// //                 j++;
// //             }
// //             char **command = ft_split(split[i], ' ');
// //             if (execve(command[0], command, environ) == -1) 
// //             {
// //                 perror("execve");
// //                 exit(EXIT_FAILURE);
// //             }
// //         }
// //         else 
// //         {
// //             // Parent process
// //             if (i < num_commands - 1) 
// //             {
// //                 close(pipes[i][WRITE_END]);
// //                 in_fd = pipes[i][READ_END];
// //             }
// //             if (i > 0) 
// //             {
// //                 close(pipes[i - 1][READ_END]);
// //             }
// //             wait(NULL);
// //             i++;
// //         }
// //     }    
// //     // return 0;
// // }

// void separate_commands(char **split, char *command1[], char *command2[]) 
// {
//     printf("separate_commands========>>>>> \n");
//     int i = 0;
//     int j = 0;
//     int k = 0;
//     int pipe_found = 0;
    
//     while (split[i] != NULL) {
//         if (strcmp(split[i], "|") == 0) {
//             pipe_found = 1;
//             i++;
//             continue;
//         }
//         if (pipe_found == 0) {
//             command1[j] = split[i];
//             j++;
//         } else {
//             command2[k] = split[i];
//             k++;
//         }
//         i++;
//     }
//     command1[j] = NULL;
//     command2[k] = NULL;
// }

// void execute_pipe_command(char *cmd1[], char *cmd2[], t_export **head_ex)
// {
//     (void)head_ex;
//     int fd[2];
//     pid_t pid1, pid2;
//     char *path;
    
//     if (pipe(fd) == -1) {
//         perror("pipe");
//         exit(EXIT_FAILURE);
//     }
    
//     pid1 = fork();
    
//     if (pid1 == -1) {
//         perror("fork");
//         exit(EXIT_FAILURE);
//     }  
//     if (pid1 == 0) 
//     {
//         /* child process 1 */
//         close(fd[0]); /* close read end of the pipe */
//         dup2(fd[1], STDOUT_FILENO); /* redirect stdout to the write end of the pipe */
//         close(fd[1]); /* close write end of the pipe */
//         path = check_if_command_found(cmd1[0], head_ex);
//         // printf("path1 = %s\n", path);
//         if (execve(path, cmd1, NULL) == -1) 
//         {
//             perror("execve");
//             exit(EXIT_FAILURE);
//         }
        
//     } else {
//         /* parent process */
//         pid2 = fork();
        
//         if (pid2 == -1) 
//         {
//             perror("fork");
//             exit(EXIT_FAILURE);
//         }
        
//         if (pid2 == 0) {
//             /* child process 2 */
//             close(fd[1]); /* close write end of the pipe */
//             dup2(fd[0], STDIN_FILENO); /* redirect stdin to the read end of the pipe */
//             close(fd[0]); /* close read end of the pipe */
//             // path = check_if_command_found(cmd2[0], head_ex);
//             // printf("path2 = %s\n", path);
//             if (execve(path, cmd2, NULL) == -1) 
//             {
//                 perror("execve");
//                 exit(EXIT_FAILURE);
//             }
//         } else {
//             /* parent process */
//             close(fd[0]);
//             close(fd[1]);
//             waitpid(pid1, NULL, 0);
//             waitpid(pid2, NULL, 0);
//         }
//     }
// }

// void execute_command_with_multiple_pipes(char *line)
// {
//     (void)line;
//     t_export *head_ex = NULL;
//     char **split = ft_split(line, '|');
//     char *command1[100];
//     char *command2[100];
//     separate_commands(split, command1, command2);
//     execute_pipe_command(command1, command2, &head_ex);
// }

// function to check if the command is built in or not
// int check_if_command_is_built_in(char *command, char *args[], t_export **head_ex)

void execute_command_with_multiple_pipes(char *line, char **environ, t_export **heda_ex)
{
    (void)environ;
    char **commands = ft_split(line, '|');
    int nm = 0;
    int num_commands = 0;
    char *path;
    while (commands[num_commands])
        num_commands++;
        
    while (commands[nm])
    {
        if (check_if_command_found(ft_split(commands[nm], ' ')[0], heda_ex) == NULL)
        {
            printf("minishell: %s: command not found\n", commands[nm]);
            return ;
        }
        nm++;
    }
    
    int pipes[num_commands - 1][2];
    int i = 0;
    while (i < num_commands - 1)
    {
        if (pipe(pipes[i]) == -1)
        {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
        i++;
    }
    i = 0;
    int in_fd = 0;
    while (i < num_commands)
    {
        path = check_if_command_found(ft_split(commands[i], ' ')[0], heda_ex);
        // printf("path = %s\n", path);
        pid_t pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if (pid == 0)
        {
            // Child process
            if (i < num_commands - 1)
            {
                if (dup2(pipes[i][WRITE_END], STDOUT_FILENO) == -1)
                {
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }
            }
            if (i > 0)
            {
                if (dup2(in_fd, STDIN_FILENO) == -1)
                {
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }
            }
            int j = 0;
            while (j < num_commands - 1)
            {
                close(pipes[j][READ_END]);
                close(pipes[j][WRITE_END]);
                j++;
            }
            char **command = ft_split(commands[i], ' ');
            print_list_export(*heda_ex);
            if (execve(path, command, NULL) == -1) 
            {
                printf("Error");
                perror("execveeeeeee");
                exit(EXIT_FAILURE);
            }
        }
        else 
        {
            // Parent process
            if (i < num_commands - 1) 
            {
                close(pipes[i][WRITE_END]);
                in_fd = pipes[i][READ_END];
            }
            if (i > 0) 
            {
                close(pipes[i - 1][READ_END]);
            }
            wait(NULL);
            i++;
        }
    } 
}

int check_if_there_is_pipe(char **ft_split)
{
    int i = 0;  
    while (ft_split[i])
    {
        if (!ft_strcmp(ft_split[i], "|"))
            return (1);
        i++;
    }
    return 0;
}