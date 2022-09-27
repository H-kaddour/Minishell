/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 22:02:51 by hkaddour          #+#    #+#             */
/*   Updated: 2022/09/27 17:20:53 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void  pipeline(t_data *data)
{
  t_cmd *trav;
  int   i;
  int   pid;
  int   fd[2];
  //int   fd_hold;

  i = 0;
  trav = data->v_cmd;
  while (trav->next)
  {
    if (pipe(fd))
    {
		  printf("error in pipe\n");
      return ;
    }
    trav->f_out = fd[1];
    trav = trav->next;
    trav->f_in = fd[0];
  }
  //**trav = data->v_cmd;
  //**while (trav)
  //**{
  //**  //here if cmd have redirection close here pipe where it reads or write depends
  //**  check_redirection(data, trav);
  //**  trav = trav->next;
  //**}
  trav = data->v_cmd;
  i = 0;
  char ptr[10] = {0};
  //pipe(fd);
  while (trav)
  {
    //pipe(fd);
    //printf("cmd = %s    in = %d    out = %d\n", trav->cmd[0], trav->f_in, trav->f_out);
    //printf("cmd = %s    in = %d    out = %d\n", trav->cmd[0], trav->f_in, trav->f_out);
    pid = fork();
    if (pid < 0)
    {
      printf("error in fork\n");
      exit(0);
    }
    if (pid == 0)
    {
      //close(fd[1]);
      //if (i == 0)
      //{
      //  //dup2(0, STDIN_FILENO);
      //  dup2(fd_hold, STDOUT_FILENO);
      //  //dup2(fd[1], STDOUT_FILENO);
      //}
      //if (i != 0)
      //{
      //  dup2(fd[0], STDIN_FILENO);
      //  //dup2(1, STDOUT_FILENO);
      //}
      //else
      //  dup2(1, STDOUT_FILENO);
      //if (i == 0)
      //  dup2(0, STDIN_FILENO);


      //here i should close pipe of fork so i should loop for the pipe
      //printf("cmd = %s    in = %d    out = %d\n", trav->cmd[0], trav->f_in, trav->f_out);
      //if (trav->f_in > 0)
      //close(trav->f_in);
      //**dup2(trav->f_in, STDIN_FILENO);
      //if (trav->f_out > 1)
      if (trav->next)
      {
        //close(trav->f_in);
        dup2(trav->f_out, STDOUT_FILENO);
      }
      if (!trav->next)
      {
        //close(trav->f_out);
        dup2(trav->f_in, STDIN_FILENO);
      }
      //close(trav->f_in);
      //if (trav->f_out > 1)
      //  close(trav->f_out);
      //printf("in = %d    out = %d\n", trav->f_in, trav->f_out);
      get_path(data, trav);
      //exit(0);
    }
    read(trav->f_out, &ptr, 9);
    printf("**%s**\n", ptr);
    //while (1);
    //if (pid == 1)
    //{
		//  //signal(SIGINT, SIG_IGN);
    //  wait(0);
    //  //close(fd[0]);
    //  //fd_hold = fd[1];
    //}
    trav = trav->next;
    //i++;
  }
  //trav = data->v_cmd;
  //while (trav)
  //{
  //  close(trav->f_in);
  //  close(trav->f_out);
  //  trav = trav->next;
  //}
  //i = 0;
  //trav = data->v_cmd;
  while(1)
  {
    if (waitpid(-1, NULL, 0) == -1)
      break;
  }
  //close(trav->f_in);
  //close(trav->f_out);
  //while (i < 2)
  //{
  //  wait(0);
  //  //exit(0);
  //  //if (trav->f_in > 0)
  //  //  close(trav->f_in);
  //  i++;
  //  trav = trav->next;
  //}
}
//pseudo code:
//first i will make the pipes for the size_of_cmd - 1
//loop for the cmd nodes and initialize in and out with their pipes values
//then check if there's redirection if yes close in or out pipe in node and replace it with red files
//make another loop on cmd nodes and start execting the cmd
