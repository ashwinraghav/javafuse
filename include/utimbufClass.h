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

#ifndef _UTIMBUFCLASS_H_
#define _UTIMBUFCLASS_H_

#include "includes.h"
#include <utime.h>

typedef struct
{
    jfieldID actime;
    jfieldID modtime;

    jmethodID Ctor;
    jmethodID finalize;
} utimbufClassID;

void init_utimbufClass();
void copyUtimbufIn(struct utimbuf *buf, jobject jbuf);
void copyUtimbufOut(jobject jbuf, struct utimbuf *buf);

#endif
