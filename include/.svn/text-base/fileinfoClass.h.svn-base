/*
 * JavaFuse - Java bindings for using FUSE.
 * Copyright (C) 2009 SRI International
 * 
 * This program is free software: you can redistribute it and/or modify it under 
 * the terms of the GNU General Public License as published by the Free Software 
 * Foundation, either version 3 of the License, or (at your option) any later 
 * version.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT 
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS 
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along with 
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _FILEINFOCLASS_H_
#define _FILEINFOCLASS_H_

#include "includes.h"

typedef struct
{
    jfieldID flags;
    jfieldID fh_old;
    jfieldID writepage;
    jfieldID direct_io;
    jfieldID keep_cache;
    jfieldID flush;
    jfieldID padding;
    jfieldID fh;
    jfieldID lock_owner;

    jmethodID Ctor;
    jmethodID finalize;
} fileinfoClassID;

void init_fileinfoClass();
void copyInfoIn(struct fuse_file_info *info, jobject jinfo);
void copyInfoOut(jobject jinfo, struct fuse_file_info *info);

#endif
