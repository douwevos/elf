/*
   File:    shoivalue.c
   Project: shoveler
   Author:  Douwe Vos
   Date:    Oct 5, 2014
   e-mail:  dmvos2000(at)yahoo.com

   Copyright (C) 2014 Douwe Vos.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#include "shoivalue.h"

G_DEFINE_INTERFACE(ShoIValue, sho_ivalue, G_TYPE_OBJECT);

static void sho_ivalue_default_init (ShoIValueInterface *iface) {
	iface->deepCopy = NULL;
}

ShoIValue *sho_ivalue_deep_copy(ShoIValue *self) {
	g_return_val_if_fail(SHO_IS_IVALUE(self), NULL);
	return SHO_IVALUE_GET_INTERFACE(self)->deepCopy(self);
}
