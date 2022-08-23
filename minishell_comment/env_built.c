/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_built.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 12:52:21 by hkaddour          #+#    #+#             */
/*   Updated: 2022/08/14 10:10:42 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void  reinit_env(t_data *data)
{
  t_env *trav;

  //here don't get env again cuz i still have env just change it the pwd
  //get_env(data);
  trav = data->l_env;
  while (ft_strncmp(trav->sec, "PWD", 3))
    trav = trav->next;
  //if (trav->value[])
  //if (ft_strlen(trav->value) > 1)
  //  free(trav->value);
  //trav->value = malloc(sizeof(char) * ft_strlen(data->cd_path) + 1);
  trav->value = data->cd_path;
}

void  pwd_cmd(t_data *data)
{
  t_env *trav;

  trav = data->l_env;
  while (ft_strncmp(trav->sec, "PWD", 3))
    trav = trav->next;
  printf("%s\n", trav->value);
  //if (data->built_cmd->type == WRD)
  //{
  //  printf("%s\n", trav->value);
  //}
}

void  env_cmd(t_data *data)
{
  //maybe all white space check
  t_env *trav;

  trav = data->l_env;
  //if (data->built_cmd->next->type == W_SPACE || data->built_cmd->next == NULL)
  if (data->built_cmd->next != NULL)
  {
    if (data->built_cmd->next->type != W_SPACE)
    {
      error("minishel: env env no\n", 1);
      return ;
    }
  }//I have to check error in all the line
  if (/*data->built_cmd->next->type == W_SPACE ||*/ data->built_cmd != NULL)
  {
    while (trav->next)
    {
      printf("%s=%s\n", trav->sec, trav->value);
      trav = trav->next;
    }
  }
  //else
  //  error("minishel: env env no\n", 1);
}

int check_quotes(t_token *quote)
{
  int i;
  int j;
  t_token *quotes;
  
  i = 0;
  quotes = quote;
  while (quotes)
  {
    if (quotes->type == D_QUOT)
    {
      j = 0;
      while (quotes->value[j] == '"')
      {
        i++;
        j++;
      }
      //break ;
      //i++;
    }
    quotes = quotes->next;
  }
  if (i % 2 == 0)
    return (0);
  //else if (i % 2 == 1)
  else
    return (1);
}

void  print_env_var(t_data *data)
{
  t_env *trav;

  trav = data->l_env;
  while (trav)
  {
    printf("declare -x %s=\"%s\"\n", trav->sec, trav->value);
    trav = trav->next;
  }
}

int check_if_exist(t_data *data, t_token *trav)
{
  int   i;
  int   j;
  t_env *env;
  char  *str;
  
  i = 0;
  env = data->l_env;
  while (trav->value[i] != '=' && trav->value[i])
    i++;
  str = malloc(sizeof(char) * i + 1);
  j = 0;
  while (trav->value[j] != trav->value[i] /*&& trav->value[j] != '"'*/)
  {
    str[j] = trav->value[j];
    j++;
  }
  str[j] = 0;
  while (ft_strncmp(env->sec, str, i) && env->next != NULL)
  {
    env = env->next;
  }
  data->var_exist = env;
  if (!ft_strncmp(env->sec, str, i))
    return (1);
  else
    return (0);
  //{
  //  data->var_exist = env;
  //  return (1);
  //}
  //return (0);
}

void  unset_cmd(t_data *data)
{
  t_token *trav;

  trav = data->t_token;
  if (trav->next->type == W_SPACE)
  {
    trav = trav->next;
    //here double quote alone "niga" 'hhah'
    if (trav->next->type == WRD)
    {

    }
    else
    {
      //error function
    }
  }
  else
  {
    //error function
  }

}

void  export_cmd(t_data *data)
{
  int     i;
  int     j;
  t_token *trav;
  t_env   *tail;
  t_env   *middle_man;

  tail = data->l_env;
  while (tail->next)
    tail = tail->next;
  if (data->built_cmd->type == WRD)
  {
    //here print the whole env with var
    if (data->built_cmd->next == NULL || data->built_cmd->next->type == D_QUOT ||\
        data->built_cmd->next->type == S_QUOT)
    {
      print_env_var(data);
      return ;
      //printf("error or some shiit");
      //here u should print env plus var with shiit
    }
    //if (data->built_cmd->next->type != W_SPACE)
    //  error("minishell: export space after u son of a hoe", 1);
    trav = data->built_cmd->next;
    while (trav)
    {
      //if (trav->next != NULL)
      //  trav = trav->next;
      if (trav->type == W_SPACE)
      {
        if (trav->next == NULL)
        {
          printf("\n");
          return ;
        }
        trav = trav->next;
      }
      if (trav->type != WRD && trav->type != D_QUOT)
      {
        error("minishell: only wrd and quotes", 1);
        return ;
      }
      else
      {
        //
        if (trav->type == D_QUOT)
        {
          //var for this func
          char  *pp;
          char  *ptr;
          //check if the quote are close
          if (!check_quotes(trav))
          {
            trav = trav->next;
            //here check if the variable is already exist in env
            //what about if "hey" with no equal sign
            if (check_if_exist(data, trav))
            {
              int   n;
              //int   m;
              int   len;

              //pp = ft_strchr(trav->value, '=');
              n = 0;
              while (data->line[n] && data->line[n] != '=')
                n++;
              pp = &data->line[++n];
              len = ft_strlen(pp);
              ptr = malloc(sizeof(char) * len);
              //m = n;
              i = 0;
              while (pp[i])
              {
                if (pp[i] != '"')
                  ptr[i] = pp[i];
                i++;
              }
              ptr[i] = 0;
              data->var_exist->value = ptr;
              return ;
              //data->var_exist this var point in where the var are in env
              //gad blan "" and signle ones
              //gad blan shlllvl
              //blan unset
              //gD to go to a funciton
            }
            else
            {
              i = 0;
              while (trav->value[i] && trav->value[i] != '=')
                i++;
              pp = trav->value;
              pp[i] = 0;
              middle_man = node_allocate(data);
              middle_man->sec = pp;
              i = 0;
              while (data->line[i] && data->line[i] != '=')
                i++;
              pp = &data->line[++i];
              i = 0;
              ptr = malloc(sizeof(char) * ft_strlen(pp));
              while (pp[i])
              {
                if (pp[i] != '"')
                  ptr[i] = pp[i];
                i++;
              }
              ptr[i] = 0;
              middle_man->value = ptr;
              tail->next = middle_man;
              //trav = trav->next;

              //here i should put in the ptr var in the env
              //here finish if var is not exist
              //printf("%s", pp);
              return ;
            }
          }
          else
          {
            //use function of error.
            printf("quote are not close");
            exit(0);
            return ;
          }
        }
        //
        if (trav->type == WRD)
        {
          if (check_if_exist(data, trav))
          {
            i = 0;
            while (trav->value[i] != '=' && trav->value[i])
              i++;
            if (trav->value[i] == '=')
            {
              if (trav->value[++i] != 0)
              {
                //data->var_exist->value = &trav->value[i];
                data->var_exist->value = ft_strdup(&trav->value[i]);
              }
              else
              {
                data->var_exist->value = ft_strdup("");
              }
            }
            else
            {
              return ;
              //continue ;
              //trav = trav->next;
            }
          }
          else
          {
            i = 0;
            while (trav->value[i] != '=' && trav->value[i])
              i++;
            middle_man = node_allocate(data);
            middle_man->sec = malloc(sizeof(char) * i + 1);
            j = 0;
            while (trav->value[j] != trav->value[i])
            {
              middle_man->sec[j] = trav->value[j];
              j++;
            }
            middle_man->sec[j] = 0;
            if (trav->value[i] == '=')
            {
              if (trav->value[++i] != 0)
              {
                j = 0;
                //j = ft_strlen(&trav->value[i]);
                middle_man->value = malloc(sizeof(char) * ft_strlen(&trav->value[i]) + 1);
                while (trav->value[i] != 0)
                {
                  middle_man->value[j] = trav->value[i];
                  j++;
                  i++;
                }
                middle_man->value[j] = 0;
              }
              else
              {
                middle_man->value = ft_strdup(0);
              }
            }
            else
            {
              middle_man->value = ft_strdup("");
            }
            tail->next = middle_man;
            middle_man->next = NULL;
          }
        }
      }
      tail = middle_man;
      trav = trav->next;
    }
    ///if (trav->next != NULL)
    ///{
    ///  trav = trav->next;
    ///  //if (trav->type == W_SPACE)
    ///  //{
    ///  //  while (trav->type == W_SPACE)
    ///  //    trav = trav->next;
    ///  //}
    ///  while (trav->type == W_SPACE)
    ///    trav = trav->next;
    ///  //i have to add > redirect and $ in "" and single quote
    ///  if (trav->type != WRD && trav->type != D_QUOT)
    ///  {
    ///    error("minishell: only wrd and quotes", 1);
    ///  }
    ///  else
    ///  {
    ///    if (trav->type == WRD)
    ///    {
    ///      i = 0;
    ///      while (trav->value[i] != '=' && trav->value[i])
    ///        i++;
    ///      middle_man = node_allocate(data);
    ///      middle_man->sec = malloc(sizeof(char) * i + 1);
    ///      j = 0;
    ///      while (trav->value[j] != trav->value[i])
    ///      {
    ///        middle_man->sec[j] = trav->value[j];
    ///        j++;
    ///      }
    ///      middle_man->sec[j] = 0;
    ///      if (trav->value[i] == '=')
    ///      {
    ///        if (trav->value[++i] != 0)
    ///        {
    ///          j = 0;
    ///          //j = ft_strlen(&trav->value[i]);
    ///          middle_man->value = malloc(sizeof(char) * ft_strlen(&trav->value[i]) + 1);
    ///          while (trav->value[i] != 0)
    ///          {
    ///            middle_man->value[j] = trav->value[i];
    ///            j++;
    ///            i++;
    ///          }
    ///          middle_man->value[j] = 0;
    ///        }
    ///        else
    ///        {
    ///          middle_man->value = ft_strdup(0);
    ///        }
    ///      }
    ///      tail->next = middle_man;
    ///      middle_man->next = NULL;
    ///    }
    ///  }
      //if (trav->type == WRD || trav->type == D_QUOT)
      //{

      //}
      //if (trav->type == WRD)
        //here check what kind of word and add it to env
      //while (trav)
      //{
      //  if (trav->type != W_SPACE)
      //  if (trav->type != W_SPACE && trav->type != WRD)
      //  {
      //    error("minishell: export space after u son of a hoe", 1);
      //  }
      //  trav = trav->next;
      //}
    //}
  }
}


//handle a lot of echos and "" and $ on it
void  echo_cmd(t_data *data)
{
  t_token *trav;

  if (data->built_cmd->next == NULL)
    printf("empty line\n");//take that msg off later
  if (data->built_cmd->next != NULL)
  {
    if (data->built_cmd->next->type == D_QUOT ||\
        data->built_cmd->next->type == S_QUOT)
    {
      if (check_quotes(data->built_cmd->next))
        error("minishell: close quotes", 1);
      else
        printf("\n");
        //return ;
    }
    else if (data->built_cmd->next->type != W_SPACE)
    {
      error("minishell: you need to sprate with space", 1);
      return ;
    }
    ///here
    if (data->built_cmd->next->type == W_SPACE)
    {
      trav = data->built_cmd->next;
      if (trav->next == NULL)
        printf("\n");
      trav = trav->next;
      while (trav)
      {
        //if dolla sign
        //check if the list have the quote close
        //and `single quote
        if (trav->type == D_QUOT)
        {
          if (check_quotes(trav))
            error("minishell: close quotes", 1);
          else
          {
            if (trav->next != NULL)
              trav = trav->next;
            while (trav->type != D_QUOT)
            {
              printf("%s", trav->value);
              trav = trav->next;
            }
            trav = trav->next;
            if (trav == NULL)
            {
              printf("\n");
              return ;
            }
          }
            //print_quote(trav);
        }
        if (trav->type == W_SPACE)
          trav->value = " ";
        //if (trav->type != D_QUOT)
        printf("%s", trav->value);
        trav = trav->next;
      }
      printf("\n");
      //if (trav->next->type == WRD)
      //{
      //  trav = trav->next;
      //  while (trav)
      //  {
      //    //if (trav->type == )
      //    //here check if the next value have $ or "" and more
      //    //
      //    printf("%s", trav->value);
      //    trav = trav->next;
      //  }
      //  printf("\n");
      //}
    }
  }
  //if (data->built_cmd->next->type != W_SPACE)
  //{
  //  error("minishell: you need to sprate with space", 1);
  //  return ;
  //}
  ///if (data->built_cmd->next->type == W_SPACE)
  ///{
  ///  trav = data->built_cmd->next;
  ///  if (trav->next->type == NULL)
  ///  if (trav->next->type == WRD)
  ///  {
  ///    trav = trav->next;
  ///    while (trav)
  ///    {
  ///      //if (trav->type == )
  ///      //here check if the next value have $ or "" and more
  ///      //
  ///      printf("%s", trav->value);
  ///      trav = trav->next;
  ///    }
  ///    printf("\n");
  ///  }
  ///}
}










