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


#include "golem.h"

typedef struct _GolemBlockPrivate GolemBlockPrivate;

struct _GolemBlockPrivate
{
  GList * statements;
};

struct _GolemBlock
{
  GolemStatement parent_instance;
  GolemBlockPrivate * priv;
};

G_DEFINE_TYPE_WITH_PRIVATE(GolemBlock,golem_block,GOLEM_TYPE_STATEMENT)

gboolean
_golem_block_execute(GolemStatement * statement,GolemRuntime * runtime,GError ** error)
{
  gboolean done = TRUE;
  golem_runtime_enter(runtime,GOLEM_RUNTIME_LOCAL);
  GList * statements = GOLEM_BLOCK(statement)->priv->statements;
  for(GList * iter = g_list_first(statements);iter;iter = g_list_next(iter))
    {
      GolemStatement * statement = GOLEM_STATEMENT(iter->data);
      done = golem_statement_execute(statement,runtime,error);
      if(!done || !golem_runtime_running(runtime))
	break;
    }
  golem_runtime_exit(runtime);
  return done;
}

static void
golem_block_init(GolemBlock * self)
{
  self->priv = golem_block_get_instance_private(self);
  self->priv->statements = NULL;
}

static void
golem_block_class_init(GolemBlockClass * klass)
{
  GOLEM_STATEMENT_CLASS(klass)->execute = _golem_block_execute;
}

gboolean
golem_block_check(GolemParser * parser)
{
  return golem_parser_is_next_word(parser,"{");
}

GolemBlock *
golem_block_parse(GolemParser * parser,GError ** error)
{
  GolemBlock * self = GOLEM_BLOCK(g_object_new(GOLEM_TYPE_BLOCK,NULL));
  if(golem_parser_next_word_check(parser,"{"))
    {
      while(!golem_parser_is_end(parser))
	{
	   if(golem_parser_next_word_check(parser,"}"))
	     break;

	   GolemStatement * sentence = golem_statement_parse(parser,error);
	   if(sentence)
	     {
	       self->priv->statements = g_list_append(self->priv->statements,sentence);
	     }
	   else
	     {
	       g_clear_object(&self);
	       break;
	     }
	}
    }
  return self;
}
