/*
   File:    chauowremovetext.h
   Project: chameleon
   Author:  Douwe Vos
   Date:    Feb 23, 2015
   e-mail:  dmvos2000(at)yahoo.com

   Copyright (C) 2015 Douwe Vos.

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

#ifndef CHAUOWREMOVETEXT_H_
#define CHAUOWREMOVETEXT_H_

#include "chauow.h"
#include <caterpillar.h>

G_BEGIN_DECLS

#define CHA_TYPE_UOW_REMOVE_TEXT              (cha_uow_remove_text_get_type())
#define CHA_UOW_REMOVE_TEXT(obj)              (G_TYPE_CHECK_INSTANCE_CAST ((obj), cha_uow_remove_text_get_type(), ChaUowRemoveText))
#define CHA_UOW_REMOVE_TEXT_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), CHA_TYPE_UOW_REMOVE_TEXT, ChaUowRemoveTextClass))
#define CHA_IS_UOW_REMOVE_TEXT(obj)           (G_TYPE_CHECK_INSTANCE_TYPE ((obj), CHA_TYPE_UOW_REMOVE_TEXT))
#define CHA_IS_UOW_REMOVE_TEXT_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), CHA_TYPE_UOW_REMOVE_TEXT))
#define CHA_UOW_REMOVE_TEXT_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), CHA_TYPE_UOW_REMOVE_TEXT, ChaUowRemoveTextClass))


typedef struct _ChaUowRemoveText               ChaUowRemoveText;
typedef struct _ChaUowRemoveTextPrivate        ChaUowRemoveTextPrivate;
typedef struct _ChaUowRemoveTextClass          ChaUowRemoveTextClass;


struct _ChaUowRemoveText {
	ChaUow parent;
};

struct _ChaUowRemoveTextClass {
	ChaUowClass parent_class;
};


GType cha_uow_remove_text_get_type();

ChaUowRemoveText *cha_uow_remove_text_new(gboolean forward_delete, gboolean per_word);

G_END_DECLS

#endif /* CHAUOWREMOVETEXT_H_ */
