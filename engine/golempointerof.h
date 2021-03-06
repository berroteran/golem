/*
	Copyright (C) 2017 Ramiro Jose Garcia Moraga

	This file is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This file is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with the this software.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef ENGINE_GOLEMPOINTEROF_H_
#define ENGINE_GOLEMPOINTEROF_H_

typedef struct _GolemPointerOfPrivate GolemPointerOfPrivate;

#define GOLEM_TYPE_POINTER_OF	(golem_pointer_of_get_type())
G_DECLARE_FINAL_TYPE(GolemPointerOf,golem_pointer_of,GOLEM,POINTER_OF,GolemExpression)


struct _GolemPointerOfClass
{
	GolemExpressionClass parent_instance;
};

struct _GolemPointerOf
{
	GolemExpression parent_instance;
	GolemPointerOfPrivate * priv;
};


GType				golem_pointer_of_get_type(void);

gboolean			golem_pointer_of_check(GolemParser * parser);

GolemExpression * 	golem_pointer_of_parse(GolemParser * parser,GError ** error);


#endif /* ENGINE_GOLEMPOINTEROF_H_ */
