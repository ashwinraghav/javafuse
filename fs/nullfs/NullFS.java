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

/*
 * NullFS - A null filesystem using javaFUSE.
 * Implements the JavaFS interface.
 */

package nullfs;

import javafuse.*;

public class NullFS implements JavaFS
{
    public NullFS()
    {
    }

    public int getattr_pre(String path, Stat buf)
    {
        return 0;
    }

    public int getattr_post(String path, Stat buf, int result)
    {
        return 0;
    }

    public int readlink_pre(String path, String buf, int bufsize)
    {
        return 0;
    }

    public int readlink_post(String path, String buf, int bufsize, int result)
    {
        return 0;
    }

    public int mknod_pre(String path, int mode, int dev)
    {
        return 0;
    }

    public int mknod_post(String path, int mode, int dev, int result)
    {
        return 0;
    }

    public int mkdir_pre(String path, int mode)
    {
        return 0;
    }

    public int mkdir_post(String path, int mode, int result)
    {
        return 0;
    }

    public int unlink_pre(String path)
    {
        return 0;
    }

    public int unlink_post(String path, int result)
    {
        return 0;
    }

    public int rmdir_pre(String path)
    {
        return 0;
    }

    public int rmdir_post(String path, int result)
    {
        return 0;
    }

    public int symlink_pre(String oldpath, String newpath)
    {
        return 0;
    }

    public int symlink_post(String oldpath, String newpath, int result)
    {
        return 0;
    }

    public int rename_pre(String oldpath, String newpath)
    {
        return 0;
    }

    public int rename_post(String oldpath, String newpath, int result)
    {
        return 0;
    }

    public int link_pre(String oldpath, String newpath)
    {
        return 0;
    }

    public int link_post(String oldpath, String newpath, int result)
    {
        return 0;
    }

    public int chmod_pre(String path, int mod)
    {
        return 0;
    }

    public int chmod_post(String path, int mod, int result)
    {
        return 0;
    }

    public int chown_pre(String path, int owner, int group)
    {
        return 0;
    }

    public int chown_post(String path, int owner, int group, int result)
    {
        return 0;
    }

    public int truncate_pre(String path, int length)
    {
        return 0;
    }

    public int truncate_post(String path, int length, int result)
    {
        return 0;
    }

    public int utime_pre(String filename, Utimbuf buf)
    {
        return 0;
    }

    public int utime_post(String filename, Utimbuf buf, int result)
    {
        return 0;
    }

    public int open_pre(String path, Fuse_file_info info)
    {
        return 0;
    }

    public int open_post(String path, Fuse_file_info info, int result)
    {
        return 0;
    }

    public int read_pre(String path, String buf, int size, int offset, Fuse_file_info info)
    {
        return 0;
    }

    public int read_post(String path, String buf, int size, int offset, Fuse_file_info info, int result)
    {
        return 0;
    }

    public int write_pre(String path, String buf, int count, int offset, Fuse_file_info info)
    {
        return 0;
    }

    public int write_post(String path, String buf, int count, int offset, Fuse_file_info info, int result)
    {
        return 0;
    }

    public int statfs_pre(String path, Statvfs buf)
    {
        return 0;
    }

    public int statfs_post(String path, Statvfs buf, int result)
    {
        return 0;
    }

    public int flush_pre(String path, Fuse_file_info info)
    {
        return 0;
    }

    public int flush_post(String path, Fuse_file_info info, int result)
    {
        return 0;
    }

    public int release_pre(String path, Fuse_file_info info)
    {
        return 0;
    }

    public int release_post(String path, Fuse_file_info info, int result)
    {
        return 0;
    }

    public int fsync_pre(String path, int datasync, Fuse_file_info info)
    {
        return 0;
    }

    public int fsync_post(String path, int datasync, Fuse_file_info info, int result)
    {
        return 0;
    }

    public int setxattr_pre(String path, String name, String value, int size, int flags)
    {
        return 0;
    }

    public int setxattr_post(String path, String name, String value, int size, int flags, int result)
    {
        return 0;
    }

    public int getxattr_pre(String path, String name, String value, int size)
    {
        return 0;
    }

    public int getxattr_post(String path, String name, String value, int size, int result)
    {
        return 0;
    }

    public int listxattr_pre(String path, String list, int size)
    {
        return 0;
    }

    public int listxattr_post(String path, String list, int size, int result)
    {
        return 0;
    }

    public int removexattr_pre(String path, String name)
    {
        return 0;
    }

    public int removexattr_post(String path, String name, int result)
    {
        return 0;
    }

    public int opendir_pre(String path, Fuse_file_info info)
    {
        return 0;
    }

    public int opendir_post(String path, Fuse_file_info info, int result)
    {
        return 0;
    }

    public int readdir_pre(String path, long buf, long filler, int offset, Fuse_file_info info)
    {
        return 0;
    }

    public int readdir_post(String path, long buf, long filler, int offset, Fuse_file_info info, int result)
    {
        return 0;
    }

    public int releasedir_pre(String path, Fuse_file_info info)
    {
        return 0;
    }

    public int releasedir_post(String path, Fuse_file_info info, int result)
    {
        return 0;
    }

    public int fsyncdir_pre(String path, int datasync, Fuse_file_info info)
    {
        return 0;
    }

    public int fsyncdir_post(String path, int datasync, Fuse_file_info info, int result)
    {
        return 0;
    }

    public void init(Fuse_conn_info conn)
    {
    }

    public void destroy(long arg)
    {
    }

    public int access_pre(String path, int mode)
    {
        return 0;
    }

    public int access_post(String path, int mode, int result)
    {
        return 0;
    }

    public int create_pre(String path, int mode, Fuse_file_info info)
    {
        return 0;
    }

    public int create_post(String path, int mode, Fuse_file_info info, int result)
    {
        return 0;
    }

    public int ftruncate_pre(String path, int length, Fuse_file_info info)
    {
        return 0;
    }

    public int ftruncate_post(String path, int length, Fuse_file_info info, int result)
    {
        return 0;
    }

    public int fgetattr_pre(String path, Stat st, Fuse_file_info info)
    {
        return 0;
    }

    public int fgetattr_post(String path, Stat st, Fuse_file_info info, int result)
    {
        return 0;
    }

    /*
       public int lock_pre(String path, Fuse_file_info info, int cmd, struct flock *lock)
       {
       return 0;
       }

       public int lock_post(String path, Fuse_file_info info, int cmd, struct flock *lock, int result)
       {
       return 0;
       }

       public int utimens_pre(String path, const struct timespec tv[2])
       {
       return 0;
       }

       public int utimens_post(String path, const struct timespec tv[2], int result)
       {
       return 0;
       }

       public int bmap_pre(String path, int blocksize, uint64_t *idx)
       {
       return 0;
       }

       public int bmap_post(String path, int blocksize, uint64_t *idx, int result)
       {
       return 0;
       }
       */

    protected void finalize()
    {
    }
}
