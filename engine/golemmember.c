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

struct _GolemMemberPrivate
{
  GolemExpression * instance;
  GolemExpression * new_value;
  gchar * index;
};

G_DEFINE_TYPE_WITH_PRIVATE(GolemMember,golem_member,GOLEM_TYPE_EXPRESSION)

static gboolean
_golem_member_evalue(GolemExpression * expression,GolemContext * context,GValue *  result,GError ** error)
{
  GolemMemberPrivate * priv = GOLEM_MEMBER(expression)->priv;
  GValue instance = G_VALUE_INIT;
  GValue new_value = G_VALUE_INIT;
  gboolean done = FALSE;

  if((done = golem_expression_evaluate(priv->instance,context,&instance,error)))
    {
      GolemTypeInfo * info = NULL;
      gboolean is_static = FALSE;
      gboolean null_pointer = TRUE;

      if(G_VALUE_HOLDS_GTYPE(&instance))
	{
	  info = golem_type_info_from_gtype(g_value_get_gtype(&instance));
	  null_pointer = FALSE;
	  is_static = TRUE;
	}
      else if(G_VALUE_HOLDS_OBJECT(&instance))
	{
	  gpointer object_instance = g_value_get_object(&instance);
	  if(object_instance) {
	      info = golem_type_info_from_gtype(G_TYPE_FROM_INSTANCE(g_value_get_object(&instance)));
	      null_pointer = FALSE;
	  }
	}
      else if(G_VALUE_HOLDS_BOXED(&instance))
	{
	  gpointer boxed = g_value_get_boxed(&instance);
	  if(boxed) {
	      info = golem_type_info_from_gtype(G_VALUE_TYPE(&instance));
	      null_pointer = FALSE;
	  }
	}
      else
	{
	  info = golem_type_info_from_gtype(G_VALUE_TYPE(&instance));
	  null_pointer = FALSE;
	}

      if(info)
	{

	  if(priv->new_value)
	    {
	      if((done = golem_expression_evaluate(priv->new_value,context,&new_value,error)))
		{
		  done = golem_type_info_set_member(info,&instance,priv->index,&new_value,error);
		  if(done)
		    {
		      g_value_init(result,G_VALUE_TYPE(&new_value));
		      g_value_copy(&new_value,result);
		    }
		  g_value_unset(&new_value);
		}
	    }
	  else
	    {
	      if(is_static)
		done = golem_type_info_get_static(info,priv->index,result,error);
	      else
		done = golem_type_info_get_member(info,&instance,priv->index,result,error);
	    }
	}
      else
	{
	  done = FALSE;
	  if(null_pointer)
	    golem_runtime_error(error,GOLEM_NULL_POINTER_ERROR,"can't access member of null");
	  else
	    golem_runtime_error(error,GOLEM_NOT_IMPLEMENTED_ERROR,"no member implementation for the type");
	}
      g_value_unset(&instance);
    }
  return done;
}

static void
golem_member_init(GolemMember * self)
{
  self->priv = golem_member_get_instance_private(self);
  self->priv->instance = NULL;
  self->priv->new_value = NULL;
  self->priv->index = NULL;
}

static void
golem_member_class_init(GolemMemberClass * klass)
{
  GOLEM_EXPRESSION_CLASS(klass)->evaluate = _golem_member_evalue;
}

gboolean
golem_member_check(GolemParser * parser)
{
  gboolean checked = FALSE;
  golem_parser_save_point(parser);
  if(golem_parser_next_word_check(parser,"."))
    {
      checked = golem_parser_check_is_named(parser);
    }
  golem_parser_restore_point(parser);
  return checked;
}

GolemExpression *
golem_member_parse(GolemParser * parser,GolemExpression * instance,GolemExpressionLimit limit,GError ** error)
{
  gboolean done = FALSE;
  GolemMember * expression = GOLEM_MEMBER(g_object_new(GOLEM_TYPE_MEMBER,NULL));
  expression->priv->instance = instance;
  if(golem_parser_next_word_check(parser,"."))
    {
      if(golem_parser_check_is_named(parser))
	{
	  expression->priv->index = g_strdup(golem_parser_next_word(parser,NULL,TRUE));
	  if(golem_parser_next_word_check(parser,"="))
	    {
	      expression->priv->new_value = golem_expression_complex_parse(parser,limit,error);
	      done = expression->priv->new_value != NULL;
	    }
	  else
	    {
	      done = TRUE;
	    }
	}
      else
	{
	  golem_parser_error(error,parser,"was expected the member name");
	}
    }

  if(!done)
    {
      g_object_unref(expression);
      expression = NULL;
    }
  return GOLEM_EXPRESSION(expression);
}
