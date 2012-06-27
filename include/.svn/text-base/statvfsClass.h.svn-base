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

#ifndef _STATVFSCLASS_H_
#define _STATVFSCLASS_H_

#include "includes.h"
#include <sys/statvfs.h>

typedef struct
{
    jfieldID f_bsize;
    jfieldID f_frsize;
    jfieldID f_blocks;
    jfieldID f_bfree;
    jfieldID f_bavail;
    jfieldID f_files;
    jfieldID f_ffree;
    jfieldID f_favail;
    jfieldID f_fsid;
    jfieldID f_flag;
    jfieldID f_namemax;

    jmethodID Ctor;
    jmethodID finalize;
} statvfsClassID;

void init_statvfsClass();
void copyStatvfsIn(struct statvfs *buf, jobject statvfsObj);
void copyStatvfsOut(jobject statvfsObj, struct statvfs *buf);

#endif
