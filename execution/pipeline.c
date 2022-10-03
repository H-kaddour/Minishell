/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 22:02:51 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/03 14:57:23 by hkaddour         ###   ########.fr       */
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
  //int   **pipe_fds;

  //pipe_fds = malloc(sizeof(int *) * 2);
  t_cmd *trav;
  int   i;
  //int   j;
  int   pid;
  int   fd[2];
  //char  rd[10] = {0};
  //int   fd_hold;

  i = 0;
  trav = data->v_cmd;
  //trav->tab_pipe = malloc(sizeof(int *) * data->size_cmd - 1);
  while (trav->next)
  {
    i = 0;
    if (pipe(fd))
    {
		  printf("error in pipe\n");
      return ;
    }
    //pipe_fds[i] = malloc(sizeof(int) * 2);
    //pipe_fds[i][j++] = fd[1];
    //pipe_fds[i][j] = fd[0];
    trav->tab_pipe = malloc(sizeof(int) * 2);
    trav->tab_pipe[i++] = fd[1];
    trav->tab_pipe[i] = fd[0];
    trav->f_out = fd[1];
    trav = trav->next;
    trav->f_in = fd[0];
    //printf("%d  %d\n", pipe_fds[i][0], pipe_fds[i][1]);
    //i++;
  }
  //j = 0;
  i = 0;
  trav->tab_pipe = malloc(sizeof(int) * 2);
  trav->tab_pipe[i++] = fd[1];
  trav->tab_pipe[i] = fd[0];

  trav = data->v_cmd;
  while (trav)
  {
    i = 0;
    while (i < 2)
    {
      printf("%d ", trav->tab_pipe[i]);
      i++;
    }
    printf("\n");
    trav = trav->next;
  }

  //**trav = data->v_cmd;
  //**while (trav)
  //**{
  //**  //here if cmd have redirection close here pipe where it reads or write depends
  //**  check_redirection(data, trav);
  //**  trav = trav->next;
  //**}
  //printf("hey\n");
  t_cmd *p_trav;
  i = 0;

  trav = data->v_cmd;
  //p_trav = data->v_cmd;
  //**printf("\n");
  //**printf("%d  ", trav->tab_pipe[0]);
  //**printf("%d", trav->tab_pipe[1]);
  //**trav = trav->next;
  //**printf("\n");
  //**printf("%d  ", trav->tab_pipe[0]);
  //**printf("%d", trav->tab_pipe[1]);
  //i = 0;
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
      //if (i == 0)
      //  close(trav->f_in);
      //if (!trav->next)
      //  close(trav->f_out);
      printf("%d\n", i);
      printf("%s\n", trav->cmd[0]);
      dup2(trav->f_out, STDOUT_FILENO);
      dup2(trav->f_in, STDIN_FILENO);
      //close(fd[0]);
      //close(fd[1]);
        close(trav->tab_pipe[0]);
        close(trav->tab_pipe[1]);
      //if (trav->f_in > 0)
      //  close(trav->f_in);
      //if (trav->f_out > 1)
      //  close(trav->f_out);
      //if (trav->cmd[0][0] == 'w')

      //if (trav->cmd[0][0] == 'w')
      //{
      //  printf("here\n");
      //  while (1);
      //}
      execute_sys_cmd(data, trav);
      //close(trav->f_in);
      //close(trav->f_out);
    }
    if (pid >= 1)
    {
      close(trav->tab_pipe[0]);
      close(trav->tab_pipe[1]);
      waitpid(pid, NULL, 0);
      //trav = trav->next;
    }
    trav = trav->next;
    i++;
  }

  //trav = data->v_cmd;
  //while(p_trav)
  p_trav = data->v_cmd;
  //while(1)
  //while(p_trav)
  //while(1)
  //while(p_trav)
  //{
  //  //close(fd[0]);
  //  //close(fd[1]);
  //    //printf("in parent %d\n", i);
  //    printf("in parent %s\n", p_trav->cmd[0]);
  //    //printf("in parent dial trav %s\n", trav->cmd[0]);
  //    //if (p_trav->next)
  //    //{
  //      printf("parent closing file\n");
  //      close(p_trav->tab_pipe[0]);
  //      close(p_trav->tab_pipe[1]);
  //    //}
  //  //waitpid(trav->pid, NULL, 0);
  //  //wait(0);
  //  //trav = trav->next;
  //  //if (wait(0))
  //  //if (waitpid(-1, NULL, 0) == -1)
  //  //waitpid(pid, NULL, 0);
  //    //p_trav = p_trav->next;
  //  if (waitpid(pid, &status, 0) == 0)
  //  {
  //    p_trav = p_trav->next;
  //    printf("hye\n");
  //    //trav = trav->next;
  //    break;
  //  }
  //  printf("status %d\n", status);
  //  printf("end of loop\n");
  //  //p_trav = p_trav->next;
  //}
  //printf("im out\n");

}
//pseudo code:
//first i will make the pipes for the size_of_cmd - 1
//loop for the cmd nodes and initialize in and out with their pipes values
//then check if there's redirection if yes close in or out pipe in node and replace it with red files
//make another loop on cmd nodes and start execting the cmd
