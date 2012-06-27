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

#include "statClass.h"
#include "javafuse_jni.h"
#include "includes.h"
#include <sys/stat.h>

extern fuseStruct fuseSt;

/*
 * Initilize the stat class.
 */
void init_statClass()
{
    JNIEnv *env = get_env();

    jclass _statClass = (*env)->FindClass(env, "javafuse/Stat");
    fuseSt.statClass = (*env)->NewGlobalRef(env, _statClass);
    assert(fuseSt.statClass != NULL);

    fuseSt.statID.Ctor = (*env)->GetMethodID(env, fuseSt.statClass, "<init>", "()V");
    assert(fuseSt.statID.Ctor != NULL);

    fuseSt.statID.finalize = (*env)->GetMethodID(env, fuseSt.statClass, "finalize", "()V");
    assert(fuseSt.statID.finalize != NULL);

    fuseSt.statID.st_dev = (*env)->GetFieldID(env, fuseSt.statClass, "st_dev", "J");
    assert(fuseSt.statID.st_dev != NULL);
    fuseSt.statID.st_ino = (*env)->GetFieldID(env, fuseSt.statClass, "st_ino", "J");
    assert(fuseSt.statID.st_ino != NULL);
    fuseSt.statID.st_mode = (*env)->GetFieldID(env, fuseSt.statClass, "st_mode", "J");
    assert(fuseSt.statID.st_mode != NULL);
    fuseSt.statID.st_nlink = (*env)->GetFieldID(env, fuseSt.statClass, "st_nlink", "J");
    assert(fuseSt.statID.st_nlink != NULL);
    fuseSt.statID.st_uid = (*env)->GetFieldID(env, fuseSt.statClass, "st_uid", "J");
    assert(fuseSt.statID.st_uid != NULL);
    fuseSt.statID.st_gid = (*env)->GetFieldID(env, fuseSt.statClass, "st_gid", "J");
    assert(fuseSt.statID.st_gid != NULL);
    fuseSt.statID.st_rdev = (*env)->GetFieldID(env, fuseSt.statClass, "st_rdev", "J");
    assert(fuseSt.statID.st_rdev != NULL);
    fuseSt.statID.st_size = (*env)->GetFieldID(env, fuseSt.statClass, "st_size", "J");
    assert(fuseSt.statID.st_size != NULL);
    fuseSt.statID.st_blksize = (*env)->GetFieldID(env, fuseSt.statClass, "st_blksize", "J");
    assert(fuseSt.statID.st_blksize != NULL);
    fuseSt.statID.st_blocks = (*env)->GetFieldID(env, fuseSt.statClass, "st_blocks", "J");
    assert(fuseSt.statID.st_blocks != NULL);
    fuseSt.statID.st_atimee = (*env)->GetFieldID(env, fuseSt.statClass, "st_atime", "J");
    assert(fuseSt.statID.st_atimee != NULL);
    fuseSt.statID.st_mtimee = (*env)->GetFieldID(env, fuseSt.statClass, "st_mtime", "J");
    assert(fuseSt.statID.st_mtimee != NULL);
    fuseSt.statID.st_ctimee = (*env)->GetFieldID(env, fuseSt.statClass, "st_ctime", "J");
    assert(fuseSt.statID.st_ctimee != NULL);

    release_env(env);
}

/*
 * Copy to stat struct from stat object.
 */
void copyStatIn(struct stat *buf, jobject statObj)
{
    JNIEnv *env = get_env();

    buf->st_dev = (*env)->GetLongField(env, statObj, fuseSt.statID.st_dev);
    buf->st_ino = (*env)->GetLongField(env, statObj, fuseSt.statID.st_ino);
    buf->st_mode = (*env)->GetLongField(env, statObj, fuseSt.statID.st_mode);
    buf->st_nlink = (*env)->GetLongField(env, statObj, fuseSt.statID.st_nlink);
    buf->st_uid = (*env)->GetLongField(env, statObj, fuseSt.statID.st_uid);
    buf->st_gid = (*env)->GetLongField(env, statObj, fuseSt.statID.st_gid);
    buf->st_rdev = (*env)->GetLongField(env, statObj, fuseSt.statID.st_rdev);
    buf->st_size = (*env)->GetLongField(env, statObj, fuseSt.statID.st_size);
    buf->st_blksize = (*env)->GetLongField(env, statObj, fuseSt.statID.st_blksize);
    buf->st_blocks = (*env)->GetLongField(env, statObj, fuseSt.statID.st_blocks);
    buf->st_atime = (*env)->GetLongField(env, statObj, fuseSt.statID.st_atimee);
    buf->st_mtime = (*env)->GetLongField(env, statObj, fuseSt.statID.st_mtimee);
    buf->st_ctime = (*env)->GetLongField(env, statObj, fuseSt.statID.st_ctimee);

    release_env(env);
}

/*
 * Copy to stat object from stat struct.
 */
void copyStatOut(jobject statObj, struct stat *buf)
{
    JNIEnv *env = get_env();

    (*env)->SetLongField(env, statObj, fuseSt.statID.st_dev, (long) buf->st_dev);
    (*env)->SetLongField(env, statObj, fuseSt.statID.st_ino, (long) buf->st_ino);
    (*env)->SetLongField(env, statObj, fuseSt.statID.st_mode, (long) buf->st_mode);
    (*env)->SetLongField(env, statObj, fuseSt.statID.st_nlink, (long) buf->st_nlink);
    (*env)->SetLongField(env, statObj, fuseSt.statID.st_uid, (long) buf->st_uid);
    (*env)->SetLongField(env, statObj, fuseSt.statID.st_gid, (long) buf->st_gid);
    (*env)->SetLongField(env, statObj, fuseSt.statID.st_rdev, (long) buf->st_rdev);
    (*env)->SetLongField(env, statObj, fuseSt.statID.st_size, (long) buf->st_size);
    (*env)->SetLongField(env, statObj, fuseSt.statID.st_blksize, (long) buf->st_blksize);
    (*env)->SetLongField(env, statObj, fuseSt.statID.st_blocks, (long) buf->st_blocks);
    (*env)->SetLongField(env, statObj, fuseSt.statID.st_atimee, (long) buf->st_atime);
    (*env)->SetLongField(env, statObj, fuseSt.statID.st_mtimee, (long) buf->st_mtime);
    (*env)->SetLongField(env, statObj, fuseSt.statID.st_ctimee, (long) buf->st_ctime);

    release_env(env);
}
