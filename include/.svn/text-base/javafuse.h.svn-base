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

#ifndef _JAVAFUSE_H_
#define _JAVAFUSE_H_

#include "includes.h"
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/statvfs.h>

/*
 * struct for caching directory entries.
 */
struct javafuse_dirp {
	DIR *dp;
	struct dirent *entry;
	off_t offset;
};

static int javafuse_getattr(const char *path, struct stat *buf);
static int javafuse_readlink(const char *path, char *buf, size_t bufsize);
static int javafuse_mknod(const char *path, mode_t mode, dev_t dev);
static int javafuse_mkdir(const char *path, mode_t mode);
static int javafuse_unlink(const char *path);
static int javafuse_rmdir(const char *path);
static int javafuse_symlink(const char *oldpath, const char *newpath);
static int javafuse_rename(const char *oldpath, const char *newpath);
static int javafuse_link(const char *oldpath, const char *newpath);
static int javafuse_chmod(const char *path, mode_t mod);
static int javafuse_chown(const char *path, uid_t owner, gid_t group);
static int javafuse_truncate(const char *path, off_t length);
static int javafuse_utime(const char *filename, struct utimbuf *buf);
static int javafuse_open(const char *path, struct fuse_file_info *info);
static int javafuse_read(const char *path, char *buf, size_t size, off_t offset,
        struct fuse_file_info *info);
static int javafuse_write(const char *path, const char *buf, size_t count, off_t offset, struct
        fuse_file_info *info);
static int javafuse_statfs(const char *path, struct statvfs *buf);
static int javafuse_flush(const char *path, struct fuse_file_info *info);
static int javafuse_release(const char *path, struct fuse_file_info *info);
static int javafuse_fsync(const char *path, int datasync, struct fuse_file_info *info);
static int javafuse_setxattr(const char *path, const char *name, const char *value,
        size_t size, int flags);
static int javafuse_getxattr(const char *path, const char *name, char *value, size_t
        size);
static int javafuse_listxattr(const char *path, char *list, size_t size);
static int javafuse_removexattr(const char *path, const char *name);
static int javafuse_opendir(const char *path, struct fuse_file_info *info);
static inline struct javafuse_dirp *get_dirp(struct fuse_file_info *info);
static int javafuse_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t
        offset, struct fuse_file_info *info);
static int javafuse_releasedir(const char *path, struct fuse_file_info *info);
static int javafuse_fsyncdir(const char *path, int datasync, struct fuse_file_info
        *info);
static void* javafuse_init(struct fuse_conn_info *conn);
static void javafuse_destroy(void *arg);
static int javafuse_access(const char *path, int mode);
static int javafuse_create(const char *path, mode_t mode, struct fuse_file_info *info);
static int javafuse_ftruncate(const char *path, off_t length, struct fuse_file_info
        *info);
static int javafuse_fgetattr(const char *path, struct stat *st, struct fuse_file_info
        *info);
static int javafuse_lock(const char *path, struct fuse_file_info *info, int cmd, struct
        flock *lock);
static int javafuse_utimens(const char *path, const struct timespec tv[2]);
static int javafuse_bmap(const char *path, size_t blocksize, uint64_t *idx);

static void read_cmdline(int argc, char *argv[]); 
static void read_config(const char *path);

#endif
