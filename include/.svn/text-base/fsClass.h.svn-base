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

#ifndef _FSCLASS_H_
#define _FSCLASS_H_

#include <fuse.h>
#include <jni.h>

typedef struct
{
    jmethodID Ctor;
    jmethodID getattr_pre;
    jmethodID getattr_post;
    jmethodID readlink_pre;
    jmethodID readlink_post;
    jmethodID mknod_pre;
    jmethodID mknod_post;
    jmethodID mkdir_pre;
    jmethodID mkdir_post;
    jmethodID unlink_pre;
    jmethodID unlink_post;
    jmethodID rmdir_pre;
    jmethodID rmdir_post;
    jmethodID symlink_pre;
    jmethodID symlink_post;
    jmethodID rename_pre;
    jmethodID rename_post;
    jmethodID link_pre;
    jmethodID link_post;
    jmethodID chmod_pre;
    jmethodID chmod_post;
    jmethodID chown_pre;
    jmethodID chown_post;
    jmethodID truncate_pre;
    jmethodID truncate_post;
    jmethodID utime_pre;
    jmethodID utime_post;
    jmethodID open_pre;
    jmethodID open_post;
    jmethodID read_pre;
    jmethodID read_post;
    jmethodID write_pre;
    jmethodID write_post;
    jmethodID statfs_pre;
    jmethodID statfs_post;
    jmethodID flush_pre;
    jmethodID flush_post;
    jmethodID release_pre;
    jmethodID release_post;
    jmethodID fsync_pre;
    jmethodID fsync_post;
    jmethodID setxattr_pre;
    jmethodID setxattr_post;
    jmethodID getxattr_pre;
    jmethodID getxattr_post;
    jmethodID listxattr_pre;
    jmethodID listxattr_post;
    jmethodID removexattr_pre;
    jmethodID removexattr_post;
    jmethodID opendir_pre;
    jmethodID opendir_post;
    jmethodID readdir_pre;
    jmethodID readdir_post;
    jmethodID releasedir_pre;
    jmethodID releasedir_post;
    jmethodID fsyncdir_pre;
    jmethodID fsyncdir_post;
    jmethodID init;
    jmethodID destroy;
    jmethodID access_pre;
    jmethodID access_post;
    jmethodID create_pre;
    jmethodID create_post;
    jmethodID ftruncate_pre;
    jmethodID ftruncate_post;
    jmethodID fgetattr_pre;
    jmethodID fgetattr_post;
    jmethodID lock_pre;
    jmethodID lock_post;
    jmethodID utimens_pre;
    jmethodID utimens_post;
    jmethodID bmap_pre;
    jmethodID bmap_post;
    jmethodID finalize;
} fsClassID;

void init_fsClass(char *classname);

#endif
