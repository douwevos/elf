/*
   File:    chauowchangecase.h
   Project: chameleon
   Author:  Douwe Vos
   Date:    Oct 13, 2015
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

#ifndef UOW_CHAUOWCHANGECASE_H_
#define UOW_CHAUOWCHANGECASE_H_

#include "chauow.h"
#include <caterpillar.h>

G_BEGIN_DECLS

#define CHA_TYPE_UOW_CHANGE_CASE              (cha_uow_change_case_get_type())
#define CHA_UOW_CHANGE_CASE(obj)              (G_TYPE_CHECK_INSTANCE_CAST ((obj), cha_uow_change_case_get_type(), ChaUowChangeCase))
#define CHA_UOW_CHANGE_CASE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), CHA_TYPE_UOW_CHANGE_CASE, ChaUowChangeCaseClass))
#define CHA_IS_UOW_CHANGE_CASE(obj)           (G_TYPE_CHECK_INSTANCE_TYPE ((obj), CHA_TYPE_UOW_CHANGE_CASE))
#define CHA_IS_UOW_CHANGE_CASE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), CHA_TYPE_UOW_CHANGE_CASE))
#define CHA_UOW_CHANGE_CASE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), CHA_TYPE_UOW_CHANGE_CASE, ChaUowChangeCaseClass))

enum _ChaUowCase {
	CHA_UOW_CASE_TO_UPPER,
	CHA_UOW_CASE_TO_LOWER
};

typedef enum _ChaUowCase ChaUowCase;

typedef struct _ChaUowChangeCase               ChaUowChangeCase;
typedef struct _ChaUowChangeCasePrivate        ChaUowChangeCasePrivate;
typedef struct _ChaUowChangeCaseClass          ChaUowChangeCaseClass;


struct _ChaUowChangeCase {
	ChaUow parent;
};

struct _ChaUowChangeCaseClass {
	ChaUowClass parent_class;
};


GType cha_uow_change_case_get_type();

ChaUowChangeCase *cha_uow_change_case_new(ChaUowCase to_case);

G_END_DECLS

#endif /* UOW_CHAUOWCHANGECASE_H_ */
