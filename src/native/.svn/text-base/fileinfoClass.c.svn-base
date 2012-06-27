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

#include "fileinfoClass.h"
#include "javafuse_jni.h"
#include "includes.h"

extern fuseStruct fuseSt;

/*
 * Initilize the fuse_file_info class.
 */
void init_fileinfoClass()
{
    JNIEnv *env = get_env();

    jclass _fileinfoClass = (*env)->FindClass(env, "javafuse/Fuse_file_info");
    fuseSt.fileinfoClass = (*env)->NewGlobalRef(env, _fileinfoClass);
    assert(fuseSt.fileinfoClass != NULL);

    fuseSt.fileinfoID.Ctor = (*env)->GetMethodID(env, fuseSt.fileinfoClass, "<init>", "()V");
    assert(fuseSt.fileinfoID.Ctor != NULL);

    fuseSt.fileinfoID.finalize = (*env)->GetMethodID(env, fuseSt.fileinfoClass, "finalize", "()V");
    assert(fuseSt.fileinfoID.finalize != NULL);

    fuseSt.fileinfoID.flags = (*env)->GetFieldID(env, fuseSt.fileinfoClass, "flags", "J");
    assert(fuseSt.fileinfoID.flags != NULL);
    fuseSt.fileinfoID.fh_old = (*env)->GetFieldID(env, fuseSt.fileinfoClass, "fh_old", "J");
    assert(fuseSt.fileinfoID.fh_old != NULL);
    fuseSt.fileinfoID.writepage = (*env)->GetFieldID(env, fuseSt.fileinfoClass, "writepage", "J");
    assert(fuseSt.fileinfoID.writepage != NULL);
    fuseSt.fileinfoID.direct_io = (*env)->GetFieldID(env, fuseSt.fileinfoClass, "direct_io", "J");
    assert(fuseSt.fileinfoID.direct_io != NULL);
    fuseSt.fileinfoID.keep_cache = (*env)->GetFieldID(env, fuseSt.fileinfoClass, "keep_cache", "J");
    assert(fuseSt.fileinfoID.keep_cache != NULL);
    fuseSt.fileinfoID.flush = (*env)->GetFieldID(env, fuseSt.fileinfoClass, "flush", "J");
    assert(fuseSt.fileinfoID.flush != NULL);
    fuseSt.fileinfoID.padding = (*env)->GetFieldID(env, fuseSt.fileinfoClass, "padding", "J");
    assert(fuseSt.fileinfoID.padding != NULL);
    fuseSt.fileinfoID.fh = (*env)->GetFieldID(env, fuseSt.fileinfoClass, "fh", "J");
    assert(fuseSt.fileinfoID.fh != NULL);
    fuseSt.fileinfoID.lock_owner = (*env)->GetFieldID(env, fuseSt.fileinfoClass, "lock_owner", "J");
    assert(fuseSt.fileinfoID.lock_owner != NULL);

    release_env(env);
}

/*
 * Copy to fuse_file_info struct from fuse_file_info object.
 */
void copyInfoIn(struct fuse_file_info *info, jobject jinfo)
{
    JNIEnv *env = get_env();

    info->flags = (*env)->GetLongField(env, jinfo, fuseSt.fileinfoID.flags);
    info->fh_old = (*env)->GetLongField(env, jinfo, fuseSt.fileinfoID.fh_old);
    info->writepage = (*env)->GetLongField(env, jinfo, fuseSt.fileinfoID.writepage);
    info->direct_io = (*env)->GetLongField(env, jinfo, fuseSt.fileinfoID.direct_io);
    info->keep_cache = (*env)->GetLongField(env, jinfo, fuseSt.fileinfoID.keep_cache);
    info->flush = (*env)->GetLongField(env, jinfo, fuseSt.fileinfoID.flush);
    info->padding = (*env)->GetLongField(env, jinfo, fuseSt.fileinfoID.padding);
    info->fh = (*env)->GetLongField(env, jinfo, fuseSt.fileinfoID.fh);
    info->lock_owner = (*env)->GetLongField(env, jinfo, fuseSt.fileinfoID.lock_owner);

    release_env(env);
}

/*
 * Copy to fuse_file_info object from fuse_file_info struct.
 */
void copyInfoOut(jobject jinfo, struct fuse_file_info *info)
{
    JNIEnv *env = get_env();

    (*env)->SetLongField(env, jinfo, fuseSt.fileinfoID.flags, info->flags);
    (*env)->SetLongField(env, jinfo, fuseSt.fileinfoID.fh_old, info->fh_old);
    (*env)->SetLongField(env, jinfo, fuseSt.fileinfoID.writepage, info->writepage);
    (*env)->SetLongField(env, jinfo, fuseSt.fileinfoID.direct_io, info->direct_io);
    (*env)->SetLongField(env, jinfo, fuseSt.fileinfoID.keep_cache, info->keep_cache);
    (*env)->SetLongField(env, jinfo, fuseSt.fileinfoID.flush, info->flush);
    (*env)->SetLongField(env, jinfo, fuseSt.fileinfoID.padding, info->padding);
    (*env)->SetLongField(env, jinfo, fuseSt.fileinfoID.fh, info->fh);
    (*env)->SetLongField(env, jinfo, fuseSt.fileinfoID.lock_owner, info->lock_owner);

    release_env(env);
}
