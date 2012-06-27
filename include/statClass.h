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

#ifndef _STATCLASS_H_
#define _STATCLASS_H_

#include "includes.h"
#include <sys/stat.h>

typedef struct
{
    jfieldID st_dev;
    jfieldID st_ino;
    jfieldID st_mode;
    jfieldID st_nlink;
    jfieldID st_uid;
    jfieldID st_gid;
    jfieldID st_rdev;
    jfieldID st_size;
    jfieldID st_blksize;
    jfieldID st_blocks;

    // Notice the additional 'e' in the following names. Without this, doesn't
    // compile due to some stupid name clash caused by the system macros.
    jfieldID st_atimee;
    jfieldID st_mtimee;
    jfieldID st_ctimee;

    jmethodID Ctor;
    jmethodID finalize;
} statClassID;

void init_statClass();
void copyStatIn(struct stat *buf, jobject statObj);
void copyStatOut(jobject statObj, struct stat *buf);

#endif
