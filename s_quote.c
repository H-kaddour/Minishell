  if (typ == D_QUOT)
  {
    //here i should count how much i will allocate
    node->value = malloc(sizeof(char) * 100 + 1);
    i = 0;
    j = 0;
    while (&data->beg_line[i + 1] != &data->n_line[0] && data->beg_line[i])
    {
      while (data->beg_line[i] == '\"' || data->beg_line[i] == '\'')
      {
        if (data->beg_line[i] == '\"')
        {
          i++;
          d_quote++;
        }
        else if (data->beg_line[i] == '\'')
        {
          if (d_quote % 2 == 0)
          {
            i++;
            s_quote++;
          }
          else
          {
            s_quote++;
            node->value[j] = data->beg_line[i];
            i++;
            j++;
          }
        }
      }
      while (data->beg_line[i] == '$')
      {
        if (data->beg_line[i + 1] == ' ' || data->beg_line[i + 1] == '\"' || data->beg_line[i + 1] == '\'')
        {
          node->value[j] = data->beg_line[i];
          i++;
          j++;
          break ;
        }
        else if (data->beg_line[i + 1] == 0)
        {
          node->value[j] = data->beg_line[i];
          i++;
          j++;
          break ;
        }
        else if (data->beg_line[i + 1] == '?')
        {
          keep = i + 1;
          while (i <= keep)
          {
            node->value[j] = data->beg_line[i];
            i++;
            j++;
          }
          break ;
        }
        else if (data->beg_line[i + 1] == '$')
        {
          i += 2;
          break ;
        }
        i++;
        char  *dolla;
        int   len;

        len = 0;
        while (ft_acceptable_char(data->beg_line[i]))
        {
          i++;
          len++;
        }
        if (!(d_quote % 2 == 0 && s_quote % 2 == 1))
          dolla = malloc(sizeof(char) * len + 2);
        else
          dolla = malloc(sizeof(char) * len + 1);
        i = i - len;
        len = 0;
        if (d_quote % 2 == 0 && s_quote % 2 == 1)
        {
          dolla[len] = '$';
          len++;
        }
        while (ft_acceptable_char(data->beg_line[i]))
        {
          dolla[len] = data->beg_line[i];
          i++;
          len++;
        }
        dolla[i] = 0;
        if (!(d_quote % 2 == 0 && s_quote % 2 == 1))
        {
          while (ft_strncmp(trav_env->sec, dolla, i) && trav_env->next != NULL)
            trav_env = trav_env->next;
          if (!ft_strncmp(trav_env->sec, dolla, i))
          {
            free(dolla);
            dolla = ft_strdup(trav_env->value);
          }
          else
          {
            free(dolla);
            dolla = ft_strdup(" ");
          }
        }
        trav_env = data->l_env;
        len = 0;
        while (dolla[len])
        {
          node->value[j] = dolla[len];
          j++;
          len++;
        }
        dolla = NULL;
        while (data->beg_line[i] == '\"' || data->beg_line[i] == '\'')
        {
          if (data->beg_line[i] == '\"')
          {
            i++;
            d_quote++;
          }
          else if (data->beg_line[i] == '\'')
          {
            if (d_quote % 2 == 0)
            {
              i++;
              s_quote++;
            }
            else
            {
              s_quote++;
              node->value[j] = data->beg_line[i];
              i++;
              j++;
            }
          }
        }
      }
      while (data->beg_line[i] == '\"' || data->beg_line[i] == '\'')
      {
        if (data->beg_line[i] == '\"')
        {
          i++;
          d_quote++;
        }
        else if (data->beg_line[i] == '\'')
        {
          if (d_quote % 2 == 0)
          {
            i++;
            s_quote++;
          }
          else
          {
            s_quote++;
            node->value[j] = data->beg_line[i];
            i++;
            j++;
          }
        }
      }
      if (&data->beg_line[i + 1] == &data->n_line[0])
        break ;
        node->value[j] = data->beg_line[i];
        i++;
        j++;
    }
    data->beg_line = &data->beg_line[i];
    node->value[j] = 0;
  }
