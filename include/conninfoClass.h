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

#ifndef _CONNINFOCLASS_H_
#define _CONNINFOCLASS_H_

#include "includes.h"

typedef struct
{
    jfieldID proto_major;
    jfieldID proto_minor;
    jfieldID async_read;
    jfieldID max_write;
    jfieldID max_readahead;
    jfieldID reserved;

    jmethodID Ctor;
    jmethodID finalize;
} conninfoClassID;

void init_conninfoClass();
void copyConnIn(struct fuse_conn_info *conn, jobject jconn);
void copyConnOut(jobject jconn, struct fuse_conn_info *conn);

#endif
