/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 22:02:51 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/01 09:21:59 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void  run(t_data *data, char *cmd)
{
  char *c1;
  char *ll;
  char **sp;

  if (cmd[0] == 'l')
  {
    c1 = ft_strjoin("/bin/", cmd);
    ll = "ls -la";
    sp = ft_split(ll, ' ');
  }
  else if (cmd[0] == 'g')
  {
    c1 = ft_strjoin("/usr/bin/", cmd);
    ll = "grep gi";
    sp = ft_split(ll, ' ');
  }
  else if (cmd[0] == 'w')
  {
    c1 = ft_strjoin("/usr/bin/", cmd);
    ll = "wc -l";
    sp = ft_split(ll, ' ');
  }
  execve(c1, sp, data->env);
}

void  pipeline(t_data *data)
{
  t_cmd *trav;
  int   i;
  int   pid;
  int   fd[2];
  //char  rd[10] = {0};
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
  //char ptr[10] = {0};
  //pipe(fd);
  //while (i < 2)
  while (trav)
  {
    //pipe(fd);
    //printf("cmd = %s    in = %d    out = %d\n", trav->cmd[0], trav->f_in, trav->f_out);
    //printf("cmd = %s    in = %d    out = %d\n", trav->cmd[0], trav->f_in, trav->f_out);
    pid = fork();
    if (pid < 0)
    {
      printf("error in fork\n");
      exit(2);
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
      //**if (trav->next)
      //**{
      //**  //close(trav->f_in);
      //**  dup2(trav->f_out, STDOUT_FILENO);
      //**}
      //**if (!trav->next)
      //**{
      //**  //close(trav->f_out);
      //**  dup2(trav->f_in, STDIN_FILENO);
      //**}
      //if (i != 3)
        dup2(trav->f_out, STDOUT_FILENO);
      //if (i != 0)
        dup2(trav->f_in, STDIN_FILENO);
      //close(trav->f_in);
      //if (trav->f_out > 1)
      //  close(trav->f_out);
      //printf("in = %d    out = %d\n", trav->f_in, trav->f_out);
      //get_path(data, trav);
      execute_sys_cmd(data, trav);
      //*run(data, trav->cmd[0]);
      //exit(0);
      //*read(trav->f_in, &rd, 9);
      //*printf("%s\n", rd);
      //free(rd);
      //printf("hey \n");
      break ;
      //return ;
      //exit(1);
    }
    //read(trav->f_out, &ptr, 9);
    //printf("**%s**\n", ptr);
    //while (1);
    //else
    //{
		//  //signal(SIGINT, SIG_IGN);
    //  //wait(0);
    //  waitpid(pid, NULL, 0);
    //  //if (read(trav->f_in, &rd, 9) <= 0)
    //  //  printf("file empty\n");
    //  //printf("\n**%s\n", rd);
    //  //close(fd[0]);
    //  //fd_hold = fd[1];
    //  trav = trav->next;
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

  //**this one works
  //while ((wait(0) != -1 || errno != ECHILD))
  //{
  //  printf("hey\n");
  //}
  while(1)
  {
    //waitpid(trav->pid, NULL, 0);
    //wait(0);
    //trav = trav->next;
    //if (wait(0))
    //if (waitpid(-1, NULL, 0) == -1)
    if (waitpid(pid, NULL, 0) == -1)
    {
      break;
    }
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
