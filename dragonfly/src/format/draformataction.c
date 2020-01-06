/*
   File:    draformataction.c
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

#include "draformataction.h"

#include <logging/catlogdefs.h>
#define CAT_LOG_LEVEL CAT_LOG_ALL
#define CAT_LOG_CLAZZ "DraFormatAction"
#include <logging/catlog.h>

struct _DraFormatActionPrivate {
	DraFormatLocation in_left;
	DraFormatLocation in_right;
	DraFormatLocation out_left;
	DraFormatLocation out_right;
};

G_DEFINE_TYPE_WITH_CODE(DraFormatAction, dra_format_action, G_TYPE_OBJECT,  // @suppress("Unused static function")
	G_ADD_PRIVATE(DraFormatAction)
);

static void l_dispose(GObject *object);
static void l_finalize(GObject *object);

static void dra_format_action_class_init(DraFormatActionClass *clazz) {
	GObjectClass *object_class = G_OBJECT_CLASS(clazz);
	object_class->dispose = l_dispose;
	object_class->finalize = l_finalize;
}

static void dra_format_action_init(DraFormatAction *instance) {
}

static void l_dispose(GObject *object) {
	cat_log_detail("dispose:%p", object);
//	DraFormatAction *instance = DRA_FORMAT_ACTION(object);
//	DraFormatActionPrivate *priv = dra_format_action_get_instance_private(instance);
	G_OBJECT_CLASS(dra_format_action_parent_class)->dispose(object);
	cat_log_detail("disposed:%p", object);
}

static void l_finalize(GObject *object) {
	cat_log_detail("finalize:%p", object);
	cat_ref_denounce(object);
	G_OBJECT_CLASS(dra_format_action_parent_class)->finalize(object);
	cat_log_detail("finalized:%p", object);
}


DraFormatAction *dra_format_action_new(DraFormatLocation in_left, DraFormatLocation in_right, DraFormatLocation out_left, DraFormatLocation out_right) {
	DraFormatAction *result = g_object_new(DRA_TYPE_FORMAT_ACTION, NULL);
	cat_ref_anounce(result);
	DraFormatActionPrivate *priv = dra_format_action_get_instance_private(result);
	priv->in_left = in_left;
	priv->in_right = in_right;
	priv->out_left = out_left;
	priv->out_right = out_right;
	return result;
}


DraFormatLocation dra_format_action_get_in_left(DraFormatAction *action) {
	DraFormatActionPrivate *priv = dra_format_action_get_instance_private(action);
	return priv->in_left;
}

DraFormatLocation dra_format_action_get_in_right(DraFormatAction *action) {
	DraFormatActionPrivate *priv = dra_format_action_get_instance_private(action);
	return priv->in_right;
}

DraFormatLocation dra_format_action_get_out_left(DraFormatAction *action) {
	DraFormatActionPrivate *priv = dra_format_action_get_instance_private(action);
	return priv->out_left;
}

DraFormatLocation dra_format_action_get_out_right(DraFormatAction *action) {
	DraFormatActionPrivate *priv = dra_format_action_get_instance_private(action);
	return priv->out_right;
}

