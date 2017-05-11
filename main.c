/*
	Copyright (C) 2016 Ramiro Jose Garcia Moraga

	This file is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 2 of the License, or
	(at your option) any later version.

	This file is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with the this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>

#include "engine/golem.h"

static gboolean
golem_print_func(GolemClosure * self,GolemClosureInvoke * invoke,gpointer data)
{
  GValue value = G_VALUE_INIT;
  while(golem_closure_invoke_next(invoke,&value))
    {
      GValue string_value = G_VALUE_INIT;
      g_value_init(&string_value,G_TYPE_STRING);
      if(g_value_transform(&value,&string_value))
	{
	  g_print("%s",g_value_get_string(&string_value));
	}
      g_value_unset(&string_value);
      g_value_unset(&value);
    }
  return TRUE;
}

static gboolean
golem_input_func(GolemClosure * self,GolemClosureInvoke * invoke,gpointer data)
{
  GValue type_value = G_VALUE_INIT;
  GValue result_value = G_VALUE_INIT;
  GType type = G_TYPE_STRING;

  if(golem_closure_invoke_next(invoke,&type_value))
    {
      if(G_VALUE_HOLDS_INT(&type_value))
	type = G_TYPE_INT;
      else if(G_VALUE_HOLDS_DOUBLE(&type_value))
	type = G_TYPE_DOUBLE;
      else if(G_VALUE_HOLDS_FLOAT(&type_value))
      	type = G_TYPE_FLOAT;
      g_value_unset(&type_value);
    }
  gchar input[1024];
  fgets(input,1024,stdin);
  g_value_init(&result_value,type);
  switch(type)
  {
    case G_TYPE_STRING:
      g_value_set_string(&result_value,input);
      break;
    case G_TYPE_INT:
      g_value_set_int(&result_value,atoi(input));
      break;
    case G_TYPE_FLOAT:
      g_value_set_float(&result_value,atof(input));
      break;
    case G_TYPE_DOUBLE:
      g_value_set_double(&result_value,atof(input));
      break;
  }
  golem_closure_invoke_set_result(invoke,&result_value);
  g_value_unset(&result_value);
  return TRUE;
}

gint
main(gint argc,gchar ** argv)
{


  GolemContext * context = golem_context_new(NULL);
  gchar * script_file_content = NULL;
  GValue  main_argc = G_VALUE_INIT,
	  main_argv = G_VALUE_INIT,
	  const_true = G_VALUE_INIT,
	  const_false = G_VALUE_INIT;

  g_value_init(&main_argc,G_TYPE_INT);
  g_value_init(&main_argv,G_TYPE_POINTER);
  g_value_init(&const_true,G_TYPE_BOOLEAN);
  g_value_init(&const_false,G_TYPE_BOOLEAN);

  g_value_set_boolean(&const_true,TRUE);
  g_value_set_boolean(&const_false,TRUE);

  golem_context_set_auto(context,"true",&const_true,NULL);
  golem_context_set_auto(context,"false",&const_false,NULL);

  GolemClosure * print_closure = golem_closure_new(golem_print_func,NULL,NULL);
  GolemClosure * input_closure = golem_closure_new(golem_input_func,NULL,NULL);

  golem_context_add_function(context,"print",print_closure);
  golem_context_add_function(context,"input",input_closure);

  g_closure_unref(G_CLOSURE(print_closure));
  g_closure_unref(G_CLOSURE(input_closure));

  g_file_get_contents("golem.glm",&script_file_content,NULL,NULL);
  GolemCompiled * compilation = golem_compiled_new();
  golem_compiled_add_string(compilation,script_file_content,-1,NULL);
  g_free(script_file_content);
  golem_compiled_run(compilation,context,NULL);
  g_object_unref(context);
  g_object_unref(compilation);

  return 0;
}

