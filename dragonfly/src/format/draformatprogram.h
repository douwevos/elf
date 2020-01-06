/*
   File:    draformatprogram.h
   Project: dragonfly
   Author:  Douwe Vos
   Date:    Dec 29, 2019
   e-mail:  dmvos2000(at)yahoo.com

   Copyright (C) 2019 Douwe Vos.

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

#ifndef DRAFORMATPROGRAM_H_
#define DRAFORMATPROGRAM_H_

#include "draformataction.h"
#include <chameleon.h>
#include <caterpillar.h>

G_BEGIN_DECLS

#define DRA_TYPE_FORMAT_PROGRAM              (dra_format_program_get_type())
#define DRA_FORMAT_PROGRAM(obj)              (G_TYPE_CHECK_INSTANCE_CAST ((obj), dra_format_program_get_type(), DraFormatProgram))
#define DRA_FORMAT_PROGRAM_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), DRA_TYPE_FORMAT_PROGRAM, DraFormatProgramClass))
#define DRA_IS_FORMAT_PROGRAM(obj)           (G_TYPE_CHECK_INSTANCE_TYPE ((obj), DRA_TYPE_FORMAT_PROGRAM))
#define DRA_IS_FORMAT_PROGRAM_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), DRA_TYPE_FORMAT_PROGRAM))
#define DRA_FORMAT_PROGRAM_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), DRA_TYPE_FORMAT_PROGRAM, DraFormatProgramClass))

struct _DraFormatProgram {
	GObject parent;
};

struct _DraFormatProgramClass {
	GObjectClass parent_class;
};

typedef struct _DraFormatProgram               DraFormatProgram;
typedef struct _DraFormatProgramPrivate        DraFormatProgramPrivate;
typedef struct _DraFormatProgramClass          DraFormatProgramClass;


GType dra_format_program_get_type();

DraFormatProgram *dra_format_program_new();

void dra_format_program_add(DraFormatProgram *program, DraFormatAction *action);

void dra_format_program_apply(DraFormatProgram *program, ChaRevisionWo *e_revision);

G_END_DECLS

#endif /* DRAFORMATPROGRAM_H_ */
