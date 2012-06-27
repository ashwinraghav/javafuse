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

#include "fsClass.h"
#include "javafuse_jni.h"
#include "includes.h"
#include <stdlib.h>
#include <stdio.h>

extern fuseStruct fuseSt;

/*
 * Get pointers to the java filesystem class and its methods.
 */
void init_fsClass(char *classname)
{
    JNIEnv *env = get_env();

    jclass _fsClass = (*env)->FindClass(env, classname);
    fuseSt.fsClass = (*env)->NewGlobalRef(env, _fsClass);
    assert(fuseSt.fsClass != NULL);

    fuseSt.fsID.Ctor = (*env)->GetMethodID(env, fuseSt.fsClass, "<init>", "()V");
    assert(fuseSt.fsID.Ctor != NULL);

    jobject _fsObj = (*env)->NewObject(env, fuseSt.fsClass, fuseSt.fsID.Ctor);
    fuseSt.fsObj = (*env)->NewGlobalRef(env, _fsObj);
    assert(fuseSt.fsObj != NULL);

    fuseSt.fsID.getattr_pre = (*env)->GetMethodID(env, _fsClass, "getattr_pre",
            "(Ljava/lang/String;Ljavafuse/Stat;)I");
    assert(fuseSt.fsID.getattr_pre != NULL);

    fuseSt.fsID.getattr_post = (*env)->GetMethodID(env, _fsClass, "getattr_post",
            "(Ljava/lang/String;Ljavafuse/Stat;I)I");
    assert(fuseSt.fsID.getattr_post != NULL);

    fuseSt.fsID.readlink_pre = (*env)->GetMethodID(env, _fsClass, "readlink_pre",
            "(Ljava/lang/String;Ljava/lang/String;I)I");
    assert(fuseSt.fsID.readlink_pre != NULL);

    fuseSt.fsID.readlink_post = (*env)->GetMethodID(env, _fsClass, "readlink_post",
            "(Ljava/lang/String;Ljava/lang/String;II)I");
    assert(fuseSt.fsID.readlink_post != NULL);

    fuseSt.fsID.mknod_pre = (*env)->GetMethodID(env, _fsClass, "mknod_pre",
            "(Ljava/lang/String;II)I");
    assert(fuseSt.fsID.mknod_pre != NULL);

    fuseSt.fsID.mknod_post = (*env)->GetMethodID(env, _fsClass, "mknod_post",
            "(Ljava/lang/String;III)I");
    assert(fuseSt.fsID.mknod_post != NULL);

    fuseSt.fsID.mkdir_pre = (*env)->GetMethodID(env, _fsClass, "mkdir_pre",
            "(Ljava/lang/String;I)I");
    assert(fuseSt.fsID.mkdir_pre != NULL);

    fuseSt.fsID.mkdir_post = (*env)->GetMethodID(env, _fsClass, "mkdir_post",
            "(Ljava/lang/String;II)I");
    assert(fuseSt.fsID.mkdir_post != NULL);

    fuseSt.fsID.unlink_pre = (*env)->GetMethodID(env, _fsClass, "unlink_pre",
            "(Ljava/lang/String;)I");
    assert(fuseSt.fsID.unlink_pre != NULL);

    fuseSt.fsID.unlink_post = (*env)->GetMethodID(env, _fsClass, "unlink_post",
            "(Ljava/lang/String;I)I");
    assert(fuseSt.fsID.unlink_post != NULL);

    fuseSt.fsID.rmdir_pre = (*env)->GetMethodID(env, _fsClass, "rmdir_pre",
            "(Ljava/lang/String;)I");
    assert(fuseSt.fsID.rmdir_pre != NULL);

    fuseSt.fsID.rmdir_post = (*env)->GetMethodID(env, _fsClass, "rmdir_post",
            "(Ljava/lang/String;I)I");
    assert(fuseSt.fsID.rmdir_post != NULL);

    fuseSt.fsID.symlink_pre = (*env)->GetMethodID(env, _fsClass, "symlink_pre",
            "(Ljava/lang/String;Ljava/lang/String;)I");
    assert(fuseSt.fsID.symlink_pre != NULL);

    fuseSt.fsID.symlink_post = (*env)->GetMethodID(env, _fsClass, "symlink_post",
            "(Ljava/lang/String;Ljava/lang/String;I)I");
    assert(fuseSt.fsID.symlink_post != NULL);

    fuseSt.fsID.rename_pre = (*env)->GetMethodID(env, _fsClass, "rename_pre",
            "(Ljava/lang/String;Ljava/lang/String;)I");
    assert(fuseSt.fsID.rename_pre != NULL);

    fuseSt.fsID.rename_post = (*env)->GetMethodID(env, _fsClass, "rename_post",
            "(Ljava/lang/String;Ljava/lang/String;I)I");
    assert(fuseSt.fsID.rename_post != NULL);

    fuseSt.fsID.link_pre = (*env)->GetMethodID(env, _fsClass, "link_pre",
            "(Ljava/lang/String;Ljava/lang/String;)I");
    assert(fuseSt.fsID.link_pre != NULL);

    fuseSt.fsID.link_post = (*env)->GetMethodID(env, _fsClass, "link_post",
            "(Ljava/lang/String;Ljava/lang/String;I)I");
    assert(fuseSt.fsID.link_post != NULL);

    fuseSt.fsID.chmod_pre = (*env)->GetMethodID(env, _fsClass, "chmod_pre",
            "(Ljava/lang/String;I)I");
    assert(fuseSt.fsID.chmod_pre != NULL);

    fuseSt.fsID.chmod_post = (*env)->GetMethodID(env, _fsClass, "chmod_post",
            "(Ljava/lang/String;II)I");
    assert(fuseSt.fsID.chmod_post != NULL);

    fuseSt.fsID.chown_pre = (*env)->GetMethodID(env, _fsClass, "chown_pre",
            "(Ljava/lang/String;II)I");
    assert(fuseSt.fsID.chown_pre != NULL);

    fuseSt.fsID.chown_post = (*env)->GetMethodID(env, _fsClass, "chown_post",
            "(Ljava/lang/String;III)I");
    assert(fuseSt.fsID.chown_post != NULL);

    fuseSt.fsID.truncate_pre = (*env)->GetMethodID(env, _fsClass, "truncate_pre",
            "(Ljava/lang/String;I)I");
    assert(fuseSt.fsID.truncate_pre != NULL);

    fuseSt.fsID.truncate_post = (*env)->GetMethodID(env, _fsClass, "truncate_post",
            "(Ljava/lang/String;II)I");
    assert(fuseSt.fsID.truncate_post != NULL);

    fuseSt.fsID.utime_pre = (*env)->GetMethodID(env, _fsClass, "utime_pre",
            "(Ljava/lang/String;Ljavafuse/Utimbuf;)I");
    assert(fuseSt.fsID.utime_pre != NULL);

    fuseSt.fsID.utime_post = (*env)->GetMethodID(env, _fsClass, "utime_post",
            "(Ljava/lang/String;Ljavafuse/Utimbuf;I)I");
    assert(fuseSt.fsID.utime_post != NULL);

    fuseSt.fsID.open_pre = (*env)->GetMethodID(env, _fsClass, "open_pre",
            "(Ljava/lang/String;Ljavafuse/Fuse_file_info;)I");
    assert(fuseSt.fsID.open_pre != NULL);

    fuseSt.fsID.open_post = (*env)->GetMethodID(env, _fsClass, "open_post",
            "(Ljava/lang/String;Ljavafuse/Fuse_file_info;I)I");
    assert(fuseSt.fsID.open_post != NULL);

    fuseSt.fsID.read_pre = (*env)->GetMethodID(env, _fsClass, "read_pre",
            "(Ljava/lang/String;Ljava/lang/String;IILjavafuse/Fuse_file_info;)I");
    assert(fuseSt.fsID.read_pre != NULL);

    fuseSt.fsID.read_post = (*env)->GetMethodID(env, _fsClass, "read_post",
            "(Ljava/lang/String;Ljava/lang/String;IILjavafuse/Fuse_file_info;I)I");
    assert(fuseSt.fsID.read_post != NULL);

    fuseSt.fsID.write_pre = (*env)->GetMethodID(env, _fsClass, "write_pre",
            "(Ljava/lang/String;Ljava/lang/String;IILjavafuse/Fuse_file_info;)I");
    assert(fuseSt.fsID.write_pre != NULL);

    fuseSt.fsID.write_post = (*env)->GetMethodID(env, _fsClass, "write_post",
            "(Ljava/lang/String;Ljava/lang/String;IILjavafuse/Fuse_file_info;I)I");
    assert(fuseSt.fsID.write_post != NULL);

    fuseSt.fsID.statfs_pre = (*env)->GetMethodID(env, _fsClass, "statfs_pre",
            "(Ljava/lang/String;Ljavafuse/Statvfs;)I");
    assert(fuseSt.fsID.statfs_pre != NULL);

    fuseSt.fsID.statfs_post = (*env)->GetMethodID(env, _fsClass, "statfs_post",
            "(Ljava/lang/String;Ljavafuse/Statvfs;I)I");
    assert(fuseSt.fsID.statfs_post != NULL);

    fuseSt.fsID.flush_pre = (*env)->GetMethodID(env, _fsClass, "flush_pre",
            "(Ljava/lang/String;Ljavafuse/Fuse_file_info;)I");
    assert(fuseSt.fsID.flush_pre != NULL);

    fuseSt.fsID.flush_post = (*env)->GetMethodID(env, _fsClass, "flush_post",
            "(Ljava/lang/String;Ljavafuse/Fuse_file_info;I)I");
    assert(fuseSt.fsID.flush_post != NULL);

    fuseSt.fsID.release_pre = (*env)->GetMethodID(env, _fsClass, "release_pre",
            "(Ljava/lang/String;Ljavafuse/Fuse_file_info;)I");
    assert(fuseSt.fsID.release_pre != NULL);

    fuseSt.fsID.release_post = (*env)->GetMethodID(env, _fsClass, "release_post",
            "(Ljava/lang/String;Ljavafuse/Fuse_file_info;I)I");
    assert(fuseSt.fsID.release_post != NULL);

    fuseSt.fsID.fsync_pre = (*env)->GetMethodID(env, _fsClass, "fsync_pre",
            "(Ljava/lang/String;ILjavafuse/Fuse_file_info;)I");
    assert(fuseSt.fsID.fsync_pre != NULL);

    fuseSt.fsID.fsync_post = (*env)->GetMethodID(env, _fsClass, "fsync_post",
            "(Ljava/lang/String;ILjavafuse/Fuse_file_info;I)I");
    assert(fuseSt.fsID.fsync_post != NULL);

    fuseSt.fsID.setxattr_pre = (*env)->GetMethodID(env, _fsClass, "setxattr_pre",
            "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;II)I");
    assert(fuseSt.fsID.setxattr_pre != NULL);

    fuseSt.fsID.setxattr_post = (*env)->GetMethodID(env, _fsClass, "setxattr_post",
            "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;III)I");
    assert(fuseSt.fsID.setxattr_post != NULL);

    fuseSt.fsID.getxattr_pre = (*env)->GetMethodID(env, _fsClass, "getxattr_pre",
            "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;I)I");
    assert(fuseSt.fsID.getxattr_pre != NULL);

    fuseSt.fsID.getxattr_post = (*env)->GetMethodID(env, _fsClass, "getxattr_post",
            "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;II)I");
    assert(fuseSt.fsID.getxattr_post != NULL);

    fuseSt.fsID.listxattr_pre = (*env)->GetMethodID(env, _fsClass, "listxattr_pre",
            "(Ljava/lang/String;Ljava/lang/String;I)I");
    assert(fuseSt.fsID.listxattr_pre != NULL);

    fuseSt.fsID.listxattr_post = (*env)->GetMethodID(env, _fsClass, "listxattr_post",
            "(Ljava/lang/String;Ljava/lang/String;II)I");
    assert(fuseSt.fsID.listxattr_post != NULL);

    fuseSt.fsID.removexattr_pre = (*env)->GetMethodID(env, _fsClass, "removexattr_pre",
            "(Ljava/lang/String;Ljava/lang/String;)I");
    assert(fuseSt.fsID.removexattr_pre != NULL);

    fuseSt.fsID.removexattr_post = (*env)->GetMethodID(env, _fsClass, "removexattr_post",
            "(Ljava/lang/String;Ljava/lang/String;I)I");
    assert(fuseSt.fsID.removexattr_post != NULL);

    fuseSt.fsID.opendir_pre = (*env)->GetMethodID(env, _fsClass, "opendir_pre",
            "(Ljava/lang/String;Ljavafuse/Fuse_file_info;)I");
    assert(fuseSt.fsID.opendir_pre != NULL);

    fuseSt.fsID.opendir_post = (*env)->GetMethodID(env, _fsClass, "opendir_post",
            "(Ljava/lang/String;Ljavafuse/Fuse_file_info;I)I");
    assert(fuseSt.fsID.opendir_post != NULL);

    fuseSt.fsID.readdir_pre = (*env)->GetMethodID(env, _fsClass, "readdir_pre",
            "(Ljava/lang/String;JJILjavafuse/Fuse_file_info;)I");
    assert(fuseSt.fsID.readdir_pre != NULL);

    fuseSt.fsID.readdir_post = (*env)->GetMethodID(env, _fsClass, "readdir_post",
            "(Ljava/lang/String;JJILjavafuse/Fuse_file_info;I)I");
    assert(fuseSt.fsID.readdir_post != NULL);

    fuseSt.fsID.releasedir_pre = (*env)->GetMethodID(env, _fsClass, "releasedir_pre",
            "(Ljava/lang/String;Ljavafuse/Fuse_file_info;)I");
    assert(fuseSt.fsID.releasedir_pre != NULL);

    fuseSt.fsID.releasedir_post = (*env)->GetMethodID(env, _fsClass, "releasedir_post",
            "(Ljava/lang/String;Ljavafuse/Fuse_file_info;I)I");
    assert(fuseSt.fsID.releasedir_post != NULL);

    fuseSt.fsID.fsyncdir_pre = (*env)->GetMethodID(env, _fsClass, "fsyncdir_pre",
            "(Ljava/lang/String;ILjavafuse/Fuse_file_info;)I");
    assert(fuseSt.fsID.fsyncdir_pre != NULL);

    fuseSt.fsID.fsyncdir_post = (*env)->GetMethodID(env, _fsClass, "fsyncdir_post",
            "(Ljava/lang/String;ILjavafuse/Fuse_file_info;I)I");
    assert(fuseSt.fsID.fsyncdir_post != NULL);

    fuseSt.fsID.init = (*env)->GetMethodID(env, _fsClass, "init",
            "(Ljavafuse/Fuse_conn_info;)V");
    assert(fuseSt.fsID.init != NULL);

    fuseSt.fsID.destroy = (*env)->GetMethodID(env, _fsClass, "destroy",
            "(J)V");
    assert(fuseSt.fsID.destroy != NULL);

    fuseSt.fsID.access_pre = (*env)->GetMethodID(env, _fsClass, "access_pre",
            "(Ljava/lang/String;I)I");
    assert(fuseSt.fsID.access_pre != NULL);

    fuseSt.fsID.access_post = (*env)->GetMethodID(env, _fsClass, "access_post",
            "(Ljava/lang/String;II)I");
    assert(fuseSt.fsID.access_post != NULL);

    fuseSt.fsID.create_pre = (*env)->GetMethodID(env, _fsClass, "create_pre",
            "(Ljava/lang/String;ILjavafuse/Fuse_file_info;)I");
    assert(fuseSt.fsID.create_pre != NULL);

    fuseSt.fsID.create_post = (*env)->GetMethodID(env, _fsClass, "create_post",
            "(Ljava/lang/String;ILjavafuse/Fuse_file_info;I)I");
    assert(fuseSt.fsID.create_post != NULL);

    fuseSt.fsID.ftruncate_pre = (*env)->GetMethodID(env, _fsClass, "ftruncate_pre",
            "(Ljava/lang/String;ILjavafuse/Fuse_file_info;)I");
    assert(fuseSt.fsID.ftruncate_pre != NULL);

    fuseSt.fsID.ftruncate_post = (*env)->GetMethodID(env, _fsClass, "ftruncate_post",
            "(Ljava/lang/String;ILjavafuse/Fuse_file_info;I)I");
    assert(fuseSt.fsID.ftruncate_post != NULL);

    fuseSt.fsID.fgetattr_pre = (*env)->GetMethodID(env, _fsClass, "fgetattr_pre",
            "(Ljava/lang/String;Ljavafuse/Stat;Ljavafuse/Fuse_file_info;)I");
    assert(fuseSt.fsID.fgetattr_pre != NULL);

    fuseSt.fsID.fgetattr_post = (*env)->GetMethodID(env, _fsClass, "fgetattr_post",
            "(Ljava/lang/String;Ljavafuse/Stat;Ljavafuse/Fuse_file_info;I)I");
    assert(fuseSt.fsID.fgetattr_post != NULL);

    // User may or may not have defined finalize, so don't assert.
    fuseSt.fsID.finalize = (*env)->GetMethodID(env, _fsClass, "finalize", "()V");
    //assert(fuseSt.fsID.finalize != NULL);

    release_env(env);
}
