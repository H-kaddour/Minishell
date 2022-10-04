/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 22:02:51 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/04 18:05:52 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



//void  pipeline(t_data *data)
//{
//	int fd[2];
//	pid_t pid;
//	t_cmd	*cmd;
//	int fdd = 0;
//	int	*tab_fd;
//	int	i;
//	int	j;
//
//	i = 0;
//	tab_fd = malloc(sizeof(int) * 4);
//	pipe(fd);
//	tab_fd[0] = fd[0];
//	tab_fd[1] = fd[1];
//	pipe(fd);
//	tab_fd[2] = fd[0];
//	tab_fd[3] = fd[1];
//	//while (i < 4)
//	//{
//	//	printf("%d\n", tab_fd[i]);
//	//	i++;
//	//}
//	i = 0;
//	j = 0;
//	cmd = data->v_cmd;
//	while (cmd)
//	{
//		if (pipe(fd) == 0)
//		{
//			printf("pipe = in=%d --- out=%d\n", fd[0], fd[1]);
//		}
//		if ((pid = fork()) == -1)
//		{
//			perror("fork");
//			exit(1);
//		}
//		else if (pid == 0)
//		{
//			printf("|child: cmd = %s\n", cmd->cmd[0]);
//			printf("	-->child:in = %d		out = %d\n", fdd, tab_fd[i+1]);
//			//printf("	-->child:in = %d		out = %d	p fdd= %d\n", tab_fd[i], tab_fd[i+1], fdd);
//			dup2(fdd, 0);
//			if (cmd->next)
//			{
//				dup2(tab_fd[i+1], 1);
//			}
//			close(fd[i]);
//			//printf("child: %s close %d\n", cmd->cmd[0], fd[0]);
//			//close(fd[1]);
//			execute_sys_cmd(data, cmd);
//			//exit(1);
//		}
//		else
//		{
//			wait(NULL);
//			close(fd[i + 1]);
//			//printf("parent: %s close %d\n", cmd->cmd[0], fd[1]);
//			fdd = tab_fd[i];
//			//while(1);
//			printf("|parent: cmd = %s\n", cmd->cmd[0]);
//			printf("	-->child:in = %d		out = %d\n", fdd, tab_fd[i+1]);
//			//printf("parent: cmd= %s		in = %d		out = %d\n", cmd->cmd[0], fd[0], fd[1]);
//			i += 2;
//			cmd = cmd->next;
//		}
//	}
//}

void  pipeline(t_data *data)
{
  t_cmd *trav;
  t_cmd *p_trav;
  int   i;
  int   j;
  //int   j;
  int   pid;
  int   fd[2];
  //char  rd[10] = {0};
  //int   fd_hold;
  //int   *fds_tab;

  i = 0;
  trav = data->v_cmd;
  //trav->tab_pipe = malloc(sizeof(int *) * data->size_cmd - 1);
  //fds_tab = malloc(sizeof(int) * (data->size_cmd - 1) * 2);
  while (trav->next)
  {
    i = 0;
    j = 0;
    if (pipe(fd))
    {
		  printf("error in pipe\n");
      return ;
    }
    trav->tab_pipe = malloc(sizeof(int) * 2);
    trav->tab_pipe[i++] = fd[1];
    trav->tab_pipe[i] = fd[0];
    trav->f_out = fd[1];
    trav = trav->next;
    trav->f_in = fd[0];
    //printf("%d  %d\n", pipe_fds[i][0], pipe_fds[i][1]);
    //i++;
  }
  //old_algo
  i = 0;
  trav->tab_pipe = malloc(sizeof(int) * 2);
  trav->tab_pipe[i++] = fd[1];
  trav->tab_pipe[i] = fd[0];

  //print the files in tab_pipe
  //trav = data->v_cmd;
  //while (trav)
  //{
  //  i = 0;
  //  while (i < 2)
  //  {
  //    printf("%d ", trav->tab_pipe[i]);
  //    i++;
  //  }
  //  printf("\n");
  //  trav = trav->next;
  //}

  trav = data->v_cmd;
  while (trav)
  {
    //here if cmd have redirection close here pipe where it reads or write depends
    check_redirection(data, trav);
    trav = trav->next;
  }
  //printf("hey\n");

  //*t_cmd *p_trav;
  //*i = 0;

  int status;
  i = 0;
  trav = data->v_cmd;
  p_trav = 0;
  while (trav)
  {
    pid = fork();
    if (pid < 0)
    {
      printf("error in fork\n");
      exit(2);
    }
    if (pid == 0)
    {
			//printf("|child: cmd = %s\n", trav->cmd[0]);
			//printf("	-->child:in = %d		out = %d\n", trav->f_in, trav->f_out);
      //dup2(trav->f_out, STDOUT_FILENO);
      //dup2(trav->f_in, STDIN_FILENO);
      //close(trav->tab_pipe[0]);
      //close(trav->tab_pipe[1]);
			if (check_builtin(&trav->cmd[0]))
      {
        //printf("Kid\n");
				builtin_cmd(data, trav);
        exit(1);
      }
      else
      {
        //printf("Cudi\n");
        dup2(trav->f_out, STDOUT_FILENO);
        dup2(trav->f_in, STDIN_FILENO);
        close(trav->tab_pipe[0]);
        close(trav->tab_pipe[1]);
        execute_sys_cmd(data, trav);
      }
    }
    if (pid > 0)
    {
		  signal(SIGINT, SIG_IGN);
		  waitpid(pid, &status, 0);
      printf("%d\n", status);
		  exit_status(&data->chk_dolla, status);
      //status = errno;
      //printf("%d\n", status);
      //printf("%d\n", errno);
      //now just exit status $?
      //fix cat 
      //wait(0);
			//if (!check_builtin(&trav->cmd[0]))
      //{
      //  if (p_trav)
      //    close(p_trav->tab_pipe[1]);
      //  close(trav->tab_pipe[0]);
      //}
      if (p_trav)
        close(p_trav->tab_pipe[1]);
      close(trav->tab_pipe[0]);
      p_trav = trav;
      trav = trav->next;
    }
  }
}
//pseudo code:
//first i will make the pipes for the size_of_cmd - 1
//loop for the cmd nodes and initialize in and out with their pipes values
//then check if there's redirection if yes close in or out pipe in node and replace it with red files
//make another loop on cmd nodes and start execting the cmd
