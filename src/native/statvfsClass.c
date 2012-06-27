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

#include "statvfsClass.h"
#include "javafuse_jni.h"
#include "includes.h"
#include <sys/statvfs.h>

extern fuseStruct fuseSt;

/*
 * Initilize the statvfs class.
 */
void init_statvfsClass()
{
    JNIEnv *env = get_env();

    jclass _statvfsClass = (*env)->FindClass(env, "javafuse/Statvfs");
    fuseSt.statvfsClass = (*env)->NewGlobalRef(env, _statvfsClass);
    assert(fuseSt.statvfsClass != NULL);

    fuseSt.statvfsID.Ctor = (*env)->GetMethodID(env, fuseSt.statvfsClass, "<init>", "()V");
    assert(fuseSt.statvfsID.Ctor != NULL);

    fuseSt.statvfsID.finalize = (*env)->GetMethodID(env, fuseSt.statvfsClass, "finalize", "()V");
    assert(fuseSt.statvfsID.finalize != NULL);

    fuseSt.statvfsID.f_bsize = (*env)->GetFieldID(env, fuseSt.statvfsClass, "f_bsize", "J");
    assert(fuseSt.statvfsID.f_bsize != NULL);
    fuseSt.statvfsID.f_frsize = (*env)->GetFieldID(env, fuseSt.statvfsClass, "f_frsize", "J");
    assert(fuseSt.statvfsID.f_frsize != NULL);
    fuseSt.statvfsID.f_blocks = (*env)->GetFieldID(env, fuseSt.statvfsClass, "f_blocks", "J");
    assert(fuseSt.statvfsID.f_blocks != NULL);
    fuseSt.statvfsID.f_bfree = (*env)->GetFieldID(env, fuseSt.statvfsClass, "f_bfree", "J");
    assert(fuseSt.statvfsID.f_bfree != NULL);
    fuseSt.statvfsID.f_bavail = (*env)->GetFieldID(env, fuseSt.statvfsClass, "f_bavail", "J");
    assert(fuseSt.statvfsID.f_bavail != NULL);
    fuseSt.statvfsID.f_files = (*env)->GetFieldID(env, fuseSt.statvfsClass, "f_files", "J");
    assert(fuseSt.statvfsID.f_files != NULL);
    fuseSt.statvfsID.f_ffree = (*env)->GetFieldID(env, fuseSt.statvfsClass, "f_ffree", "J");
    assert(fuseSt.statvfsID.f_ffree != NULL);
    fuseSt.statvfsID.f_favail = (*env)->GetFieldID(env, fuseSt.statvfsClass, "f_favail", "J");
    assert(fuseSt.statvfsID.f_favail != NULL);
    fuseSt.statvfsID.f_fsid = (*env)->GetFieldID(env, fuseSt.statvfsClass, "f_fsid", "J");
    assert(fuseSt.statvfsID.f_fsid != NULL);
    fuseSt.statvfsID.f_flag = (*env)->GetFieldID(env, fuseSt.statvfsClass, "f_flag", "J");
    assert(fuseSt.statvfsID.f_flag != NULL);
    fuseSt.statvfsID.f_namemax = (*env)->GetFieldID(env, fuseSt.statvfsClass, "f_namemax", "J");
    assert(fuseSt.statvfsID.f_namemax != NULL);

    release_env(env);
}

/*
 * Copy to statvfs struct from statvfs object.
 */
void copyStatvfsIn(struct statvfs *buf, jobject statvfsObj)
{
    JNIEnv *env = get_env();

    buf->f_bsize = (*env)->GetLongField(env, statvfsObj, fuseSt.statvfsID.f_bsize);
    buf->f_frsize = (*env)->GetLongField(env, statvfsObj, fuseSt.statvfsID.f_frsize);
    buf->f_blocks = (*env)->GetLongField(env, statvfsObj, fuseSt.statvfsID.f_blocks);
    buf->f_bfree = (*env)->GetLongField(env, statvfsObj, fuseSt.statvfsID.f_bfree);
    buf->f_bavail = (*env)->GetLongField(env, statvfsObj, fuseSt.statvfsID.f_bavail);
    buf->f_files = (*env)->GetLongField(env, statvfsObj, fuseSt.statvfsID.f_files);
    buf->f_ffree = (*env)->GetLongField(env, statvfsObj, fuseSt.statvfsID.f_ffree);
    buf->f_favail = (*env)->GetLongField(env, statvfsObj, fuseSt.statvfsID.f_favail);
    buf->f_fsid = (*env)->GetLongField(env, statvfsObj, fuseSt.statvfsID.f_fsid);
    buf->f_flag = (*env)->GetLongField(env, statvfsObj, fuseSt.statvfsID.f_flag);
    buf->f_namemax = (*env)->GetLongField(env, statvfsObj, fuseSt.statvfsID.f_namemax);

    release_env(env);
}

/*
 * Copy to statvfs object from statvfs struct.
 */
void copyStatvfsOut(jobject statvfsObj, struct statvfs *buf)
{
    JNIEnv *env = get_env();

    (*env)->SetLongField(env, statvfsObj, fuseSt.statvfsID.f_bsize, buf->f_bsize);
    (*env)->SetLongField(env, statvfsObj, fuseSt.statvfsID.f_frsize, buf->f_frsize);
    (*env)->SetLongField(env, statvfsObj, fuseSt.statvfsID.f_blocks, buf->f_blocks);
    (*env)->SetLongField(env, statvfsObj, fuseSt.statvfsID.f_bfree, buf->f_bfree);
    (*env)->SetLongField(env, statvfsObj, fuseSt.statvfsID.f_bavail, buf->f_bavail);
    (*env)->SetLongField(env, statvfsObj, fuseSt.statvfsID.f_files, buf->f_files);
    (*env)->SetLongField(env, statvfsObj, fuseSt.statvfsID.f_ffree, buf->f_ffree);
    (*env)->SetLongField(env, statvfsObj, fuseSt.statvfsID.f_favail, buf->f_favail);
    (*env)->SetLongField(env, statvfsObj, fuseSt.statvfsID.f_fsid, buf->f_fsid);
    (*env)->SetLongField(env, statvfsObj, fuseSt.statvfsID.f_flag, buf->f_flag);
    (*env)->SetLongField(env, statvfsObj, fuseSt.statvfsID.f_namemax, buf->f_namemax);

    release_env(env);
}
