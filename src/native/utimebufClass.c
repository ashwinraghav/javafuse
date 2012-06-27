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

#include "utimbufClass.h"
#include "javafuse_jni.h"
#include "includes.h"
#include <time.h>

extern fuseStruct fuseSt;

/*
 * Initilize the utimbuf class.
 */
void init_utimbufClass()
{
    JNIEnv *env = get_env();

    jclass _utimbufClass = (*env)->FindClass(env, "javafuse/Utimbuf");
    fuseSt.utimbufClass = (*env)->NewGlobalRef(env, _utimbufClass);
    assert(fuseSt.utimbufClass != NULL);

    fuseSt.utimbufID.Ctor = (*env)->GetMethodID(env, fuseSt.utimbufClass, "<init>", "()V");
    assert(fuseSt.utimbufID.Ctor != NULL);

    fuseSt.utimbufID.finalize = (*env)->GetMethodID(env, fuseSt.utimbufClass, "finalize", "()V");
    assert(fuseSt.utimbufID.finalize != NULL);

    fuseSt.utimbufID.actime = (*env)->GetFieldID(env, fuseSt.utimbufClass, "actime", "J");
    assert(fuseSt.utimbufID.actime != NULL);
    fuseSt.utimbufID.modtime = (*env)->GetFieldID(env, fuseSt.utimbufClass, "modtime", "J");
    assert(fuseSt.utimbufID.modtime != NULL);

    release_env(env);
}

/*
 * Copy to utimbuf struct from utimbuf object.
 */
void copyUtimbufIn(struct utimbuf *buf, jobject jbuf)
{
    JNIEnv *env = get_env();

    buf->actime = (*env)->GetLongField(env, jbuf, fuseSt.utimbufID.actime);
    buf->modtime = (*env)->GetLongField(env, jbuf, fuseSt.utimbufID.modtime);

    release_env(env);
}

/*
 * Copy to utimbuf object from utimbuf struct.
 */
void copyUtimbufOut(jobject jbuf, struct utimbuf *buf)
{
    JNIEnv *env = get_env();

    (*env)->SetLongField(env, jbuf, fuseSt.utimbufID.actime, buf->actime);
    (*env)->SetLongField(env, jbuf, fuseSt.utimbufID.modtime, buf->modtime);

    release_env(env);
}
