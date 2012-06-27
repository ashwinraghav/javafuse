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

#include "conninfoClass.h"
#include "javafuse_jni.h"
#include "includes.h"

extern fuseStruct fuseSt;

/*
 * Initilize the fuse_conn_info class.
 */
void init_conninfoClass()
{
    JNIEnv *env = get_env();

    jclass _conninfoClass = (*env)->FindClass(env, "javafuse/Fuse_conn_info");
    fuseSt.conninfoClass = (*env)->NewGlobalRef(env, _conninfoClass);
    assert(fuseSt.conninfoClass != NULL);

    fuseSt.conninfoID.Ctor = (*env)->GetMethodID(env, fuseSt.conninfoClass, "<init>", "()V");
    assert(fuseSt.conninfoID.Ctor != NULL);

    fuseSt.conninfoID.finalize = (*env)->GetMethodID(env, fuseSt.conninfoClass, "finalize", "()V");
    assert(fuseSt.conninfoID.finalize != NULL);

    fuseSt.conninfoID.proto_major = (*env)->GetFieldID(env, fuseSt.conninfoClass, "proto_major", "J");
    assert(fuseSt.conninfoID.proto_major != NULL);
    fuseSt.conninfoID.proto_minor = (*env)->GetFieldID(env, fuseSt.conninfoClass, "proto_minor", "J");
    assert(fuseSt.conninfoID.proto_minor != NULL);
    fuseSt.conninfoID.async_read = (*env)->GetFieldID(env, fuseSt.conninfoClass, "async_read", "J");
    assert(fuseSt.conninfoID.async_read != NULL);
    fuseSt.conninfoID.max_write = (*env)->GetFieldID(env, fuseSt.conninfoClass, "max_write", "J");
    assert(fuseSt.conninfoID.max_write != NULL);
    fuseSt.conninfoID.max_readahead = (*env)->GetFieldID(env, fuseSt.conninfoClass, "max_readahead", "J");
    assert(fuseSt.conninfoID.max_readahead != NULL);
    fuseSt.conninfoID.reserved = (*env)->GetFieldID(env, fuseSt.conninfoClass, "reserved", "[J");
    assert(fuseSt.conninfoID.reserved != NULL);

    release_env(env);
}

/*
 * Copy to fuse_conn_info struct from fuse_conn_info object.
 */
void copyConnIn(struct fuse_conn_info *conn, jobject jconn)
{
    JNIEnv *env = get_env();

    conn->proto_major = (*env)->GetLongField(env, jconn, fuseSt.conninfoID.proto_major);
    conn->proto_minor = (*env)->GetLongField(env, jconn, fuseSt.conninfoID.proto_minor);
    conn->async_read = (*env)->GetLongField(env, jconn, fuseSt.conninfoID.async_read);
    conn->max_write = (*env)->GetLongField(env, jconn, fuseSt.conninfoID.max_write);
    conn->max_readahead = (*env)->GetLongField(env, jconn, fuseSt.conninfoID.max_readahead);

    jlongArray jreserved = (*env)->GetObjectField(env, jconn, fuseSt.conninfoID.reserved);
    int length = (int) (*env)->GetArrayLength(env, jreserved);
    (*env)->GetLongArrayRegion(env, jreserved, 0, length, (jlong *)conn->reserved);

    release_env(env);
}

/*
 * Copy to fuse_conn_info object from fuse_conn_info struct.
 */
void copyConnOut(jobject jconn, struct fuse_conn_info *conn)
{
    JNIEnv *env = get_env();

    (*env)->SetLongField(env, jconn, fuseSt.conninfoID.proto_major, conn->proto_major);
    (*env)->SetLongField(env, jconn, fuseSt.conninfoID.proto_minor, conn->proto_minor);
    (*env)->SetLongField(env, jconn, fuseSt.conninfoID.async_read, conn->async_read);
    (*env)->SetLongField(env, jconn, fuseSt.conninfoID.max_write, conn->max_write);
    (*env)->SetLongField(env, jconn, fuseSt.conninfoID.max_readahead, conn->max_readahead);

    jlongArray jreserved = (*env)->GetObjectField(env, jconn, fuseSt.conninfoID.reserved);
    (*env)->SetLongArrayRegion(env, jreserved, 0, 27, (jlong *)conn->reserved);

    release_env(env);
}
