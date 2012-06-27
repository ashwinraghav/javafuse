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
 * FUSE code for simple file system that passes each system call to the
 * underlying file system.
 */

#define FUSE_USE_VERSION 28
#define _XOPEN_SOURCE 500
#define _GNU_SOURCE

#include "fsClass.h"
#include "statClass.h"
#include "statvfsClass.h"
#include "fileinfoClass.h"
#include "conninfoClass.h"
#include "utimbufClass.h"
#include "javafuse.h"
#include "javafuse_jni.h"
#include "define.h"
#include "includes.h"

#include <fuse.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/vfs.h>
#include <sys/xattr.h>
#include <sys/types.h>
#include <sys/stat.h>

extern int errno;
extern fuseStruct fuseSt;

// Define default values for configurable parameters.
static int DEBUG = 0;
static int META_DATA_ONLY = 1;
static int PRE_CALL = 1;
static int POST_CALL = 1;
static int SYS_CALL = 1;

static int fuseArgc;
static int javaArgc;
static char *fuseArgv[24];
static char *javaArgv[24];
static char *classname = NULL;
static char *configfile = NULL;

static int javafuse_getattr(const char *path, struct stat *buf)
{
    if (DEBUG) {
        PRINT_FUNC_ENTER;
    }

    // Initialization
    int res = 0;
    char *_path = strdup(path);
    assert(_path != NULL);

    jstring jpath = NULL;
    jobject jbuf = NULL;
    jint jret;
    jint jres;

    JNIEnv *env = get_env();

    // Pre Java Call
    if (PRE_CALL) {
        jpath = (*env)->NewStringUTF(env, _path);
        assert(jpath != NULL);

        jbuf = (*env)->NewObject(env, fuseSt.statClass, fuseSt.statID.Ctor);
        assert(jbuf != NULL);
        copyStatOut(jbuf, buf);

        jret = (*env)->CallIntMethod(env, fuseSt.fsObj, fuseSt.fsID.getattr_pre, jpath, jbuf);
        assert(jret != -1);

        copyStringIn(&_path, jpath);
        copyStatIn(buf, jbuf);

        if (jpath != NULL) (*env)->DeleteLocalRef(env, jpath);
        if (jbuf != NULL) (*env)->DeleteLocalRef(env, jbuf);
    }

    // Sys Call
    if (SYS_CALL) {
        res = lstat(_path, buf);
        if (res == -1) {
            free(_path);
            release_env(env);
            return -errno;
        }
    }

    // Post Java Call
    if (POST_CALL) {
        jpath = (*env)->NewStringUTF(env, _path);
        assert(jpath != NULL);

        jbuf = (*env)->NewObject(env, fuseSt.statClass, fuseSt.statID.Ctor);
        assert(jbuf != NULL);
        copyStatOut(jbuf, buf);

        jres = res;

        jret = (*env)->CallIntMethod(env, fuseSt.fsObj, fuseSt.fsID.getattr_post, jpath, jbuf, jres);
        assert(jret != -1);

        copyStringIn(&_path, jpath);
        copyStatIn(buf, jbuf);
        res = jres;

        if (jpath != NULL) (*env)->DeleteLocalRef(env, jpath);
        if (jbuf != NULL) (*env)->DeleteLocalRef(env, jbuf);
    }

    // Cleanup
    free(_path);
    release_env(env);

    return 0;
}

static int javafuse_readlink(const char *path, char *buf, size_t bufsize)
{
    if (DEBUG) {
        PRINT_FUNC_ENTER;
    }

    // Initialization
    int res = 0;
    char *_path = strdup(path);
    assert(_path);

    jstring jpath = NULL;
    jbyteArray jbuf = NULL;
    jint jbufsize;
    jint jret;
    jint jres;

    JNIEnv *env = get_env();

    // Pre Java Call
    if (PRE_CALL) {
        jpath = (*env)->NewStringUTF(env, _path);
        assert(jpath != NULL);

        jbuf = (*env)->NewByteArray(env, bufsize);
        assert(jbuf != NULL);
        (*env)->SetByteArrayRegion(env, jbuf, 0, bufsize, (jbyte *)buf);

        jbufsize = bufsize;

        jret = (*env)->CallIntMethod(env, fuseSt.fsObj, fuseSt.fsID.readlink_pre, jpath, jbuf,
                jbufsize);
        assert(jret != -1);

        // Bufsize must not change since it has been allocated by the user.
        copyStringIn(&_path, jpath);
        copyByteArrayIn(&buf, jbuf, bufsize);
        //bufsize = jbufsize;

        if (jpath != NULL) (*env)->DeleteLocalRef(env, jpath);
        if (jbuf != NULL) (*env)->DeleteLocalRef(env, jbuf);
    }

    // Sys Call
    if (SYS_CALL) {
        res = readlink(_path, buf, bufsize - 1);
        if (res == -1) {
            free(_path);
            release_env(env);
            return -errno;
        }
        buf[res] = '\0';
    }

    // Post Java Call
    if (POST_CALL) {
        jpath = (*env)->NewStringUTF(env, _path);
        assert(jpath != NULL);

        jbuf = (*env)->NewByteArray(env, bufsize);
        assert(jbuf != NULL);
        (*env)->SetByteArrayRegion(env, jbuf, 0, bufsize, (jbyte *)buf);

        jbufsize = bufsize;
        jres = res;

        jret = (*env)->CallIntMethod(env, fuseSt.fsObj, fuseSt.fsID.readlink_post, jpath, jbuf,
                jbufsize, jres);
        assert(jret == 0);

        // Bufsize must not change since it has been allocated by the user.
        copyStringIn(&_path, jpath);
        copyByteArrayIn(&buf, jbuf, bufsize);
        //bufsize = jbufsize;
        res = jres;

        if (jpath != NULL) (*env)->DeleteLocalRef(env, jpath);
        if (jbuf != NULL) (*env)->DeleteLocalRef(env, jbuf);
    }

    // Cleanup
    free(_path);
    release_env(env);

    return 0;
}

static int javafuse_mknod(const char *path, mode_t mode, dev_t dev)
{
    if (DEBUG) {
        PRINT_FUNC_ENTER;
    }

    // Initialization
    int res = 0;
    char *_path = strdup(path);
    assert(_path);

    jstring jpath = NULL;
    jint jmode;
    jint jdev;
    jint jret;
    jint jres;

    JNIEnv *env = get_env();

    // Pre Java Call
    if (PRE_CALL) {
        jpath = (*env)->NewStringUTF(env, _path);
        assert(jpath != NULL);

        jmode = mode;
        jdev = dev;

        jret = (*env)->CallIntMethod(env, fuseSt.fsObj, fuseSt.fsID.mknod_pre, jpath, jmode, jdev);
        assert(jret != -1);

        copyStringIn(&_path, jpath);
        mode = jmode;
        dev = jdev;

        if (jpath != NULL) (*env)->DeleteLocalRef(env, jpath);
    }

    // Sys Call
    if (SYS_CALL) {
        if (S_ISFIFO(mode))
            res = mkfifo(_path, mode);
        else
            res = mknod(_path, mode, dev);

        if (res == -1) {
            free(_path);
            release_env(env);
            return -errno;
        }
    }

    // Post Java Call
    if (POST_CALL) {
        jpath = (*env)->NewStringUTF(env, _path);
        assert(jpath != NULL);

        jmode = mode;
        jdev = dev;
        jres = res;

        jret = (*env)->CallIntMethod(env, fuseSt.fsObj, fuseSt.fsID.mknod_post, jpath, jmode, jdev, jres);
        assert(jret != -1);

        copyStringIn(&_path, jpath);
        mode = jmode;
        dev = jdev;
        res = jres;

        if (jpath != NULL) (*env)->DeleteLocalRef(env, jpath);
    }

    // Cleanup
    free(_path);
    release_env(env);

    return 0;
}

static int javafuse_mkdir(const char *path, mode_t mode)
{
    if (DEBUG) {
        PRINT_FUNC_ENTER;
    }

    // Initialization
    int res = 0;
    char *_path = strdup(path);
    assert(_path);

    jstring jpath = NULL;
    jint jmode;
    jint jret;
    jint jres;

    JNIEnv *env = get_env();

    // Pre Java Call
    if (PRE_CALL) {
        jpath = (*env)->NewStringUTF(env, _path);
        assert(jpath != NULL);

        jmode = mode;

        jret = (*env)->CallIntMethod(env, fuseSt.fsObj, fuseSt.fsID.mkdir_pre, jpath, jmode);
        assert(jret != -1);

        copyStringIn(&_path, jpath);
        mode = jmode;

        if (jpath != NULL) (*env)->DeleteLocalRef(env, jpath);
    }

    // Sys Call
    if (SYS_CALL) {
        res = mkdir(_path, mode);
        if (res == -1) {
            free(_path);
            release_env(env);
            return -errno;
        }
    }

    // Post Java Call
    if (POST_CALL) {
        jpath = (*env)->NewStringUTF(env, _path);
        assert(jpath != NULL);

        jmode = mode;
        jres = res;

        jret = (*env)->CallIntMethod(env, fuseSt.fsObj, fuseSt.fsID.mkdir_post, jpath, jmode, jres);
        assert(jret != -1);

        copyStringIn(&_path, jpath);
        mode = jmode;
        res = jres;

        if (jpath != NULL) (*env)->DeleteLocalRef(env, jpath);
    }

    // Cleanup
    free(_path);
    release_env(env);

    return 0; 
}

static int javafuse_unlink(const char *path)
{
    if (DEBUG) {
        PRINT_FUNC_ENTER;
    }

    // Initialization
    int res = 0;
    char *_path = strdup(path);
    assert(_path);

    jstring jpath = NULL;
    jint jret;
    jint jres;

    JNIEnv *env = get_env();

    // Pre Java Call
    if (PRE_CALL) {
        jpath = (*env)->NewStringUTF(env, _path);
        assert(jpath != NULL);

        jint jret = (*env)->CallIntMethod(env, fuseSt.fsObj, fuseSt.fsID.unlink_pre, jpath);
        assert(jret != -1);

        copyStringIn(&_path, jpath);

        if (jpath != NULL) (*env)->DeleteLocalRef(env, jpath);
    }

    // Sys Call
    if (SYS_CALL) {
        res = unlink(_path);    
        if (res == -1) {
            free(_path);
            release_env(env);
            return -errno;
        }
    }

    // Post Java Call
    if (POST_CALL) {
        jpath = (*env)->NewStringUTF(env, _path);
        assert(jpath != NULL);

        jres = res;

        jret = (*env)->CallIntMethod(env, fuseSt.fsObj, fuseSt.fsID.unlink_post, jpath, jres);
        assert(jret != -1);

        copyStringIn(&_path, jpath);
        res = jres;

        if (jpath != NULL) (*env)->DeleteLocalRef(env, jpath);
    }

    // Cleanup
    free(_path);
    release_env(env);

    return 0;
}

static int javafuse_rmdir(const char *path)
{
    if (DEBUG) {
        PRINT_FUNC_ENTER;
    }

    // Initialization
    int res = 0;
    char *_path = strdup(path);
    assert(_path);

    jstring jpath = NULL;
    jint jret;
    jint jres;

    JNIEnv *env = get_env();

    // Pre Java Call
    if (PRE_CALL) {
        jpath = (*env)->NewStringUTF(env, _path);
        assert(jpath != NULL);

        jret = (*env)->CallIntMethod(env, fuseSt.fsObj, fuseSt.fsID.rmdir_pre, jpath);
        assert(jret != -1);

        copyStringIn(&_path, jpath);

        if (jpath != NULL) (*env)->DeleteLocalRef(env, jpath);
    }

    // Sys Call
    if (SYS_CALL) {
        res = rmdir(_path);
        if (res == -1) {
            free(_path); 
            release_env(env);
            return -errno;
        }
    }

    // Post Java Call
    if (POST_CALL) {
        jpath = (*env)->NewStringUTF(env, _path);
        assert(jpath != NULL);

        jres = res;

        jret = (*env)->CallIntMethod(env, fuseSt.fsObj, fuseSt.fsID.rmdir_post, jpath, jres);
        assert(jret != -1);

        copyStringIn(&_path, jpath);
        res = jres;

        if (jpath != NULL) (*env)->DeleteLocalRef(env, jpath);
    }

    // Cleanup
    free(_path);
    release_env(env);

    return 0;
}

static int javafuse_symlink(const char *oldpath, const char *newpath)
{
    if (DEBUG) {
        PRINT_FUNC_ENTER;
    }

    // Initialization
    int res = 0;
    char *_oldpath = strdup(oldpath);
    assert(_oldpath);
    char *_newpath = strdup(newpath);
    assert(_newpath);

    jstring joldpath = NULL;
    jstring jnewpath = NULL;
    jint jret;
    jint jres;

    JNIEnv *env = get_env();

    // Pre Java Call
    if (PRE_CALL) {
        joldpath = (*env)->NewStringUTF(env, _oldpath);
        assert(joldpath != NULL);

        jnewpath = (*env)->NewStringUTF(env, _newpath);
        assert(jnewpath != NULL);

        jret = (*env)->CallIntMethod(env, fuseSt.fsObj, fuseSt.fsID.symlink_pre, joldpath, jnewpath);
        assert(jret != -1);

        copyStringIn(&_oldpath, joldpath);
        copyStringIn(&_newpath, jnewpath);

        if (joldpath != NULL) (*env)->DeleteLocalRef(env, joldpath);
        if (jnewpath != NULL) (*env)->DeleteLocalRef(env, jnewpath);
    }

    // Sys Call
    if (SYS_CALL) {
        res = symlink(_oldpath, _newpath);
        if (res == -1) {
            free(_oldpath);
            free(_newpath);
            release_env(env);
            return -errno;
        }
    }

    // Post Java Call
    if (POST_CALL) {
        joldpath = (*env)->NewStringUTF(env, _oldpath);
        assert(joldpath != NULL);

        jnewpath = (*env)->NewStringUTF(env, _newpath);
        assert(jnewpath != NULL);

        jres = res;

        jret = (*env)->CallIntMethod(env, fuseSt.fsObj, fuseSt.fsID.symlink_post, joldpath, jnewpath, jres);
        assert(jret != -1);

        copyStringIn(&_oldpath, joldpath);
        copyStringIn(&_newpath, jnewpath);
        res = jres;

        if (joldpath != NULL) (*env)->DeleteLocalRef(env, joldpath);
        if (jnewpath != NULL) (*env)->DeleteLocalRef(env, jnewpath);
    }

    // Cleanup
    free(_oldpath);
    free(_newpath);
    release_env(env);

    return 0;
}

static int javafuse_rename(const char *oldpath, const char *newpath)
{
    if (DEBUG) {
        PRINT_FUNC_ENTER;
    }

    // Initialization
    int res = 0;
    char *_oldpath = strdup(oldpath);
    assert(_oldpath);
    char *_newpath = strdup(newpath);
    assert(_newpath);

    jstring joldpath = NULL;
    jstring jnewpath = NULL;
    jint jret;
    jint jres;

    JNIEnv *env = get_env();

    // Pre Java Call
    if (PRE_CALL) {
        joldpath = (*env)->NewStringUTF(env, _oldpath);
        assert(joldpath != NULL);

        jnewpath = (*env)->NewStringUTF(env, _newpath);
        assert(jnewpath != NULL);

        jret = (*env)->CallIntMethod(env, fuseSt.fsObj, fuseSt.fsID.rename_pre, joldpath, jnewpath);
        assert(jret != -1);

        copyStringIn(&_oldpath, joldpath);
        copyStringIn(&_newpath, jnewpath);

        if (joldpath != NULL) (*env)->DeleteLocalRef(env, joldpath);
        if (jnewpath != NULL) (*env)->DeleteLocalRef(env, jnewpath);
    }

    // Sys Call
    if (SYS_CALL) {
        res = rename(_oldpath, _newpath);
        if (res == -1) {
            free(_oldpath);
            free(_newpath);
            release_env(env);
            return -errno;
        }
    }

    // Post Java Call
    if (POST_CALL) {
        joldpath = (*env)->NewStringUTF(env, _oldpath);
        assert(joldpath != NULL);

        jnewpath = (*env)->NewStringUTF(env, _newpath);
        assert(jnewpath != NULL);

        jres = res;

        jret = (*env)->CallIntMethod(env, fuseSt.fsObj, fuseSt.fsID.rename_post, joldpath, jnewpath, jres);
        assert(jret != -1);

        copyStringIn(&_oldpath, joldpath);
        copyStringIn(&_newpath, jnewpath);
        res = jres;

        if (joldpath != NULL) (*env)->DeleteLocalRef(env, joldpath);
        if (jnewpath != NULL) (*env)->DeleteLocalRef(env, jnewpath);
    }

    // Cleanup
    free(_oldpath);
    free(_newpath);
    release_env(env);

    return 0;
}

static int javafuse_link(const char *oldpath, const char *newpath)
{
    if (DEBUG) {
        PRINT_FUNC_ENTER;
    }

    // Initialization
    int res = 0;
    char *_oldpath = strdup(oldpath);
    assert(_oldpath);
    char *_newpath = strdup(newpath);
    assert(_newpath);

    jstring joldpath = NULL;
    jstring jnewpath = NULL;
    jint jret;
    jint jres;

    JNIEnv *env = get_env();

    // Pre Java Call
    if (PRE_CALL) {
        joldpath = (*env)->NewStringUTF(env, _oldpath);
        assert(joldpath != NULL);

        jnewpath = (*env)->NewStringUTF(env, _newpath);
        assert(jnewpath != NULL);

        jret = (*env)->CallIntMethod(env, fuseSt.fsObj, fuseSt.fsID.link_pre, joldpath, jnewpath);
        assert(jret != -1);

        copyStringIn(&_oldpath, joldpath);
        copyStringIn(&_newpath, jnewpath);

        if (joldpath != NULL) (*env)->DeleteLocalRef(env, joldpath);
        if (jnewpath != NULL) (*env)->DeleteLocalRef(env, jnewpath);
    }

    // Sys Call
    if (SYS_CALL) {
        res = link(_oldpath, _newpath);
        if (res == -1) {
            free(_oldpath);
            free(_newpath);
            release_env(env);
            return -errno;
        }
    }

    // Post Java Call
    if (POST_CALL) {
        joldpath = (*env)->NewStringUTF(env, _oldpath);
        assert(joldpath != NULL);

        jnewpath = (*env)->NewStringUTF(env, _newpath);
        assert(jnewpath != NULL);

        jres = res;

        jret = (*env)->CallIntMethod(env, fuseSt.fsObj, fuseSt.fsID.link_post, joldpath, jnewpath, jres);
        assert(jret != -1);

        copyStringIn(&_oldpath, joldpath);
        copyStringIn(&_newpath, jnewpath);
        res = jres;

        if (joldpath != NULL) (*env)->DeleteLocalRef(env, joldpath);
        if (jnewpath != NULL) (*env)->DeleteLocalRef(env, jnewpath);
    }

    // Cleanup
    free(_oldpath);
    free(_newpath);
    release_env(env);

    return 0;
}

static int javafuse_chmod(const char *path, mode_t mode)
{
    if (DEBUG) {
        PRINT_FUNC_ENTER;
    }

    // Initialization
    int res = 0;
    char *_path = strdup(path);
    assert(_path);

    jstring jpath = NULL;
    jint jmode;
    jint jret;
    jint jres;

    JNIEnv *env = get_env();

    // Pre Java Call
    if (PRE_CALL) {
        jpath = (*env)->NewStringUTF(env, _path);
        assert(jpath != NULL);

        jmode = mode;

        jret = (*env)->CallIntMethod(env, fuseSt.fsObj, fuseSt.fsID.chmod_pre, jpath, jmode);
        assert(jret != -1);

        copyStringIn(&_path, jpath);
        mode = jmode;

        if (jpath != NULL) (*env)->DeleteLocalRef(env, jpath);
    }

    // Sys Call
    if (SYS_CALL) {
        res = chmod(_path, mode);
        if (res == -1) {
            free(_path);
            release_env(env);
            return -errno;
        }
    }

    // Post Java Call
    if (POST_CALL) {
        jpath = (*env)->NewStringUTF(env, _path);
        assert(jpath != NULL);

        jmode = mode;
        jres = res;

        jret = (*env)->CallIntMethod(env, fuseSt.fsObj, fuseSt.fsID.chmod_post, jpath, jmode, jres);
        assert(jret != -1);

        copyStringIn(&_path, jpath);
        mode = jmode;
        res = jres;

        if (jpath != NULL) (*env)->DeleteLocalRef(env, jpath);
    }

    // Cleanup
    free(_path);
    release_env(env);

    return 0;
}

static int javafuse_chown(const char *path, uid_t owner, gid_t group)
{
    if (DEBUG) {
        PRINT_FUNC_ENTER;
    }

    // Initialization
    int res = 0;
    char *_path = strdup(path);
    assert(_path);

    jstring jpath = NULL;
    jint jowner;
    jint jgroup;
    jint jret;
    jint jres;

    JNIEnv *env = get_env();

    // Pre Java Call
    if (PRE_CALL) {
        jpath = (*env)->NewStringUTF(env, _path);
        assert(jpath != NULL);

        jowner = owner;
        jgroup = group;

        jret = (*env)->CallIntMethod(env, fuseSt.fsObj, fuseSt.fsID.chown_pre, jpath, jowner, jgroup);
        assert(jret != -1);

        copyStringIn(&_path, jpath);
        owner = jowner;
        group = jgroup;

        if (jpath != NULL) (*env)->DeleteLocalRef(env, jpath);
    }

    // Sys Call
    if (SYS_CALL) {
        res = chown(_path, owner, group);
        if (res == -1) {
            free(_path);
            release_env(env);
            return -errno;
        }
    }

    // Post Java Call
    if (POST_CALL) {
        jpath = (*env)->NewStringUTF(env, _path);
        assert(jpath != NULL);

        jowner = owner;
        jgroup = group;
        jres = res;

        jret = (*env)->CallIntMethod(env, fuseSt.fsObj, fuseSt.fsID.chown_post, jpath, jowner, jgroup, jres);
        assert(jret != -1);

        copyStringIn(&_path, jpath);
        owner = jowner;
        group = jgroup;
        res = jres;

        if (jpath != NULL) (*env)->DeleteLocalRef(env, jpath);
    }

    // Cleanup
    free(_path);
    release_env(env);

    return 0;
}

static int javafuse_truncate(const char *path, off_t length)
{
    if (DEBUG) {
        PRINT_FUNC_ENTER;
    }

    // Initialization
    int res = 0;
    char *_path = strdup(path);
    assert(_path);

    jstring jpath = NULL;
    jint jlength;
    jint jret;
    jint jres;

    JNIEnv *env = get_env();

    // Pre Java Call
    if (PRE_CALL) {
        jpath = (*env)->NewStringUTF(env, _path);
        assert(jpath != NULL);

        jlength = length;

        jret = (*env)->CallIntMethod(env, fuseSt.fsObj, fuseSt.fsID.truncate_pre, jpath, jlength);
        assert(jret != -1);

        copyStringIn(&_path, jpath);
        length = jlength;

        if (jpath != NULL) (*env)->DeleteLocalRef(env, jpath);
    }

    // Sys Call
    if (SYS_CALL) {
        res = truncate(_path, length);
        if (res == -1) {
            free(_path);
            release_env(env);
            return -errno;
        }
    }

    // Post Java Call
    if (POST_CALL) {
        jpath = (*env)->NewStringUTF(env, _path);
        assert(jpath != NULL);

        jlength = length;
        jres = res;

        jret = (*env)->CallIntMethod(env, fuseSt.fsObj, fuseSt.fsID.truncate_post, jpath, jlength, jres);
        assert(jret != -1);

        copyStringIn(&_path, jpath);
        length = jlength;
        res = jres;

        if (jpath != NULL) (*env)->DeleteLocalRef(env, jpath);
    }

    // Cleanup
    free(_path);
    release_env(env);

    return 0;
}

static int javafuse_utime(const char *path, struct utimbuf *buf)
{
    if (DEBUG) {
        PRINT_FUNC_ENTER;
    }

    // Initialization
    int res = 0;
    char *_path = strdup(path);
    assert(_path);

    jstring jpath = NULL;
    jobject jbuf = NULL;
    jint jret;
    jint jres;

    JNIEnv *env = get_env();

    // Pre Java Call
    if (PRE_CALL) {
        jpath = (*env)->NewStringUTF(env, _path);
        assert(jpath != NULL);

        jbuf = (*env)->NewObject(env, fuseSt.utimbufClass, fuseSt.statID.Ctor);
        assert(jbuf != NULL);
        copyUtimbufOut(jbuf, buf);

        jret = (*env)->CallIntMethod(env, fuseSt.fsObj, fuseSt.fsID.utime_pre, jpath, jbuf);
        assert(jret != -1);

        copyStringIn(&_path, jpath);
        copyUtimbufIn(buf, jbuf);

        if (jpath != NULL) (*env)->DeleteLocalRef(env, jpath);
        if (jbuf != NULL) (*env)->DeleteLocalRef(env, jbuf);
    }

    // Sys Call
    if (SYS_CALL) {
        res = utime(_path, buf);
        if (res == -1) {
            free(_path);
            release_env(env);
            return -errno;
        }
    }

    // Post Java Call
    if (POST_CALL) {
        jpath = (*env)->NewStringUTF(env, _path);
        assert(jpath != NULL);

        jbuf = (*env)->NewObject(env, fuseSt.utimbufClass, fuseSt.statID.Ctor);
        assert(jbuf != NULL);
        copyUtimbufOut(jbuf, buf);

        jres = res;

        jret = (*env)->CallIntMethod(env, fuseSt.fsObj, fuseSt.fsID.utime_post, jpath, jbuf, jres);
        assert(jret != -1);

        copyStringIn(&_path, jpath);
        copyUtimbufIn(buf, jbuf);
        res = jres;

        if (jpath != NULL) (*env)->DeleteLocalRef(env, jpath);
        if (jbuf != NULL) (*env)->DeleteLocalRef(env, jbuf);
    }

    // Cleanup
    free(_path);
    release_env(env);

    return 0;
}

static int javafuse_open(const char *path, struct fuse_file_info *info)
{
    if (DEBUG) {
        PRINT_FUNC_ENTER;
    }

    // Initialization
    int fd = 0;
    char *_path = strdup(path);
    assert(_path);

    jstring jpath = NULL;
    jobject jinfo = NULL;
    jint jret;
    jint jres;

    JNIEnv *env = get_env();

    // Pre Java Call
    if (PRE_CALL) {
        jpath = (*env)->NewStringUTF(env, _path);
        assert(jpath != NULL);

        jinfo = (*env)->NewObject(env, fuseSt.fileinfoClass, fuseSt.fileinfoID.Ctor);
        assert(jinfo != NULL);
        copyInfoOut(jinfo, info);

        jret = (*env)->CallIntMethod(env, fuseSt.fsObj, fuseSt.fsID.open_pre, jpath,
                jinfo);
        assert(jret != -1);

        copyStringIn(&_path, jpath);
        copyInfoIn(info, jinfo);

        if (jpath != NULL) (*env)->DeleteLocalRef(env, jpath);
        if (jinfo != NULL) (*env)->DeleteLocalRef(env, jinfo);
    }

    // Sys Call
    if (SYS_CALL) {
        fd = open(_path, info->flags);
        if (fd == -1) {
            free(_path);
            release_env(env);
            return -errno;
        }
        info->fh = fd;
    }

    // Post Java Call
    if (POST_CALL) {
        jpath = (*env)->NewStringUTF(env, _path);
        assert(jpath != NULL);

        jinfo = (*env)->NewObject(env, fuseSt.fileinfoClass, fuseSt.fileinfoID.Ctor);
        assert(jinfo != NULL);
        copyInfoOut(jinfo, info);

        jres = fd;

        jret = (*env)->CallIntMethod(env, fuseSt.fsObj, fuseSt.fsID.open_post, jpath,
                jinfo, jres);
        assert(jret != -1);

        copyStringIn(&_path, jpath);
        copyInfoIn(info, jinfo);
        fd = jres;

        if (jpath != NULL) (*env)->DeleteLocalRef(env, jpath);
        if (jinfo != NULL) (*env)->DeleteLocalRef(env, jinfo);
    }

    // Cleanup
    free(_path);
    release_env(env);

    return 0;
}

static int javafuse_read(const char *path, char *buf, size_t count, off_t offset,
        struct fuse_file_info *info)
{
    if (DEBUG) {
        PRINT_FUNC_ENTER;
    }

    // Initialization
    int res = 0;
    char *_path = strdup(path);
    assert(_path);

    jstring jpath = NULL;
    jbyteArray jbuf = NULL;
    jint jcount;
    jint joffset;
    jobject jinfo = NULL;
    jint jret;
    jint jres;

    JNIEnv *env = get_env();

    // Pre Java Call
    if (PRE_CALL) {
        jpath = (*env)->NewStringUTF(env, _path);
        assert(jpath != NULL);

        if (!META_DATA_ONLY) {
            jbuf = (*env)->NewByteArray(env, count);
            assert(jbuf != NULL);
            (*env)->SetByteArrayRegion(env, jbuf, 0, count, (jbyte *)buf);
        }

        jcount = count;
        joffset = offset;

        jinfo = (*env)->NewObject(env, fuseSt.fileinfoClass, fuseSt.fileinfoID.Ctor);
        assert(jinfo != NULL);
        copyInfoOut(jinfo, info);

        jret = (*env)->CallIntMethod(env, fuseSt.fsObj, fuseSt.fsID.read_pre, jpath, jbuf,
                jcount, joffset, jinfo);
        assert(jret != -1);

        copyStringIn(&_path, jpath);

        if (!META_DATA_ONLY)
            copyByteArrayIn(&buf, jbuf, count);

        count = jcount;
        offset = joffset;
        copyInfoIn(info, jinfo);

        if (jpath != NULL) (*env)->DeleteLocalRef(env, jpath);
        if (jbuf != NULL) (*env)->DeleteLocalRef(env, jbuf);
        if (jinfo != NULL) (*env)->DeleteLocalRef(env, jinfo);
    }

    // Sys Call
    if (SYS_CALL) {
        res = pread(info->fh, buf, count, offset);
        if (res == -1) {
            free(_path);
            release_env(env);
            return -errno;
        }
    }

    // Post Java Call
    if (POST_CALL) {
        jpath = (*env)->NewStringUTF(env, _path);
        assert(jpath != NULL);

        if (!META_DATA_ONLY) {
            jbuf = (*env)->NewByteArray(env, count);
            assert(jbuf != NULL);
            (*env)->SetByteArrayRegion(env, jbuf, 0, count, (jbyte *)buf);
        }

        jcount = count;
        joffset = offset;

        jinfo = (*env)->NewObject(env, fuseSt.fileinfoClass, fuseSt.fileinfoID.Ctor);
        assert(jinfo != NULL);
        copyInfoOut(jinfo, info);

        jres = res;

        jret = (*env)->CallIntMethod(env, fuseSt.fsObj, fuseSt.fsID.read_post, jpath, jbuf,
                jcount, joffset, jinfo, jres);
        assert(jret != -1);

        copyStringIn(&_path, jpath);

        if (!META_DATA_ONLY)
            copyByteArrayIn(&buf, jbuf, count);

        count = jcount;
        offset = joffset;
        copyInfoIn(info, jinfo);
        res = jres;

        if (jpath != NULL) (*env)->DeleteLocalRef(env, jpath);
        if (jbuf != NULL) (*env)->DeleteLocalRef(env, jbuf);
        if (jinfo != NULL) (*env)->DeleteLocalRef(env, jinfo);
    }

    // Cleanup
    free(_path);
    release_env(env);

    return res;
}

static int javafuse_write(const char *path, const char *buf, size_t count, off_t offset, struct
        fuse_file_info *info)
{
    if (DEBUG) {
        PRINT_FUNC_ENTER;
    }

    // Initialization
    int res = 0;
    char *_path = strdup(path);
    assert(_path);
    char *_buf;

    jstring jpath = NULL;
    jbyteArray jbuf = NULL;
    jint jcount;
    jint joffset;
    jobject jinfo = NULL;
    jint jret;
    jint jres;

    /* If we just want to operate on the meta-data in java, set this flag to
     * true in the config file and the buffer won't be copied to increase
     * performance.
     */
    _buf = malloc(count);
    assert(_buf != NULL);
    memcpy(_buf, buf, count);

    JNIEnv *env = get_env();

    // Pre Java Call
    if (PRE_CALL) {
        jpath = (*env)->NewStringUTF(env, _path);
        assert(jpath != NULL);

        if (!META_DATA_ONLY) {
            jbuf = (*env)->NewByteArray(env, count);
            assert(jbuf != NULL);
            (*env)->SetByteArrayRegion(env, jbuf, 0, count, (jbyte *)_buf);
        }

        jcount = count;
        joffset = offset;

        jinfo = (*env)->NewObject(env, fuseSt.fileinfoClass, fuseSt.fileinfoID.Ctor);
        assert(jinfo != NULL);
        copyInfoOut(jinfo, info);

        jret = (*env)->CallIntMethod(env, fuseSt.fsObj, fuseSt.fsID.write_pre, jpath, jbuf,
                jcount, offset, info);
        assert(jret != -1);

        copyStringIn(&_path, jpath);

        if (!META_DATA_ONLY)
            copyByteArrayIn(&_buf, jbuf, count);

        count = jcount;
        offset = joffset;
        copyInfoIn(info, jinfo);

        if (jpath != NULL) (*env)->DeleteLocalRef(env, jpath);
        if (jbuf != NULL) (*env)->DeleteLocalRef(env, jbuf);
        if (jinfo != NULL) (*env)->DeleteLocalRef(env, jinfo);
    }

    // Sys Call
    if (SYS_CALL) {
        res = pwrite(info->fh, _buf, count, offset);

        if (res == -1) {
            free(_path);
            free(_buf);
            release_env(env);
            return -errno;
        }
    }

    // Post Java Call
    if (POST_CALL) {
        jpath = (*env)->NewStringUTF(env, _path);
        assert(jpath != NULL);

        if (!META_DATA_ONLY) {
            jbuf = (*env)->NewByteArray(env, count);
            assert(jbuf != NULL);
            (*env)->SetByteArrayRegion(env, jbuf, 0, count, (jbyte *)_buf);
        }

        jcount = count;
        joffset = offset;

        jinfo = (*env)->NewObject(env, fuseSt.fileinfoClass, fuseSt.fileinfoID.Ctor);
        assert(jinfo != NULL);
        copyInfoOut(jinfo, info);

        jres = res;

        jret = (*env)->CallIntMethod(env, fuseSt.fsObj, fuseSt.fsID.write_post, jpath, jbuf,
                jcount, offset, info, jres);
        assert(jret != -1);

        copyStringIn(&_path, jpath);

        if (!META_DATA_ONLY)
            copyByteArrayIn(&_buf, jbuf, count);

        count = jcount;
        offset = joffset;
        copyInfoIn(info, jinfo);
        res = jres;

        if (jpath != NULL) (*env)->DeleteLocalRef(env, jpath);
        if (jbuf != NULL) (*env)->DeleteLocalRef(env, jbuf);
        if (jinfo != NULL) (*env)->DeleteLocalRef(env, jinfo);
    }

    // Cleanup
    free(_path);
    free(_buf);
    release_env(env);

    return res; 
}

static int javafuse_statfs(const char *path, struct statvfs *buf)
{
    if (DEBUG) {
        PRINT_FUNC_ENTER;
    }

    // Initialization
    int res = 0;
    char *_path = strdup(path);
    assert(_path);

    jstring jpath = NULL;
    jobject jbuf = NULL;
    jint jret;
    jint jres;

    JNIEnv *env = get_env();

    // Pre Java Call
    if (PRE_CALL) {
        jpath = (*env)->NewStringUTF(env, _path);
        assert(jpath != NULL);

        jbuf = (*env)->NewObject(env, fuseSt.statClass, fuseSt.statID.Ctor);
        assert(jbuf != NULL);
        copyStatvfsOut(jbuf, buf);

        jret = (*env)->CallIntMethod(env, fuseSt.fsObj, fuseSt.fsID.getattr_pre, jpath, jbuf);
        assert(jret != -1);

        copyStringIn(&_path, jpath);
        copyStatvfsIn(buf, jbuf);

        if (jpath != NULL) (*env)->DeleteLocalRef(env, jpath);
        if (jbuf != NULL) (*env)->DeleteLocalRef(env, jbuf);
    }

    // Sys Call
    if (SYS_CALL) {
        res = statvfs(_path, buf);
        if (res == -1) {
            free(_path);
            release_env(env);
            return -errno;
        }
    }

    // Post Java Call
    if (POST_CALL) {
        jpath = (*env)->NewStringUTF(env, _path);
        assert(jpath != NULL);

        jbuf = (*env)->NewObject(env, fuseSt.statClass, fuseSt.statID.Ctor);
        assert(jbuf != NULL);
        copyStatvfsOut(jbuf, buf);

        jres = res;

        jret = (*env)->CallIntMethod(env, fuseSt.fsObj, fuseSt.fsID.getattr_post, jpath, jbuf, jres);
        assert(jret != -1);

        copyStringIn(&_path, jpath);
        copyStatvfsIn(buf, jbuf);
        res = jres;

        if (jpath != NULL) (*env)->DeleteLocalRef(env, jpath);
        if (jbuf != NULL) (*env)->DeleteLocalRef(env, jbuf);
    }

    // Cleanup
    free(_path);
    release_env(env);

    return 0;
}

/*
 * Possibly flush cached data. i.e., Let the file system clean up any data
 * buffers and pass any errors in the process of closing a file to the user
 * application. Called on every close on an open file. But since flush may be
 * called multiple times for an open file, this must not really close the file
 * but rather, just flush that file.
 */
static int javafuse_flush(const char *path, struct fuse_file_info *info)
{
    if (DEBUG) {
        PRINT_FUNC_ENTER;
    }

    // Initialization
    int res = 0;
    char *_path = strdup(path);
    assert(_path);

    jstring jpath = NULL;
    jobject jinfo = NULL;
    jint jret;
    jint jres;

    JNIEnv *env = get_env();

    // Pre Java Call
    if (PRE_CALL) {
        jpath = (*env)->NewStringUTF(env, _path);
        assert(jpath != NULL);

        jinfo = (*env)->NewObject(env, fuseSt.fileinfoClass, fuseSt.fileinfoID.Ctor);
        assert(jinfo != NULL);
        copyInfoOut(jinfo, info);

        jret = (*env)->CallIntMethod(env, fuseSt.fsObj, fuseSt.fsID.flush_pre, jpath,
                jinfo);
        assert(jret != -1);

        copyStringIn(&_path, jpath);
        copyInfoIn(info, jinfo);

        if (jpath != NULL) (*env)->DeleteLocalRef(env, jpath);
        if (jinfo != NULL) (*env)->DeleteLocalRef(env, jinfo);
    }

    // Sys Call
    if (SYS_CALL) {
        res = close(dup(info->fh));
        if (res == -1) {
            free(_path);
            release_env(env);
            return -errno;
        }
    }

    // Post Java Call
    if (POST_CALL) {
        jpath = (*env)->NewStringUTF(env, _path);
        assert(jpath != NULL);

        jinfo = (*env)->NewObject(env, fuseSt.fileinfoClass, fuseSt.fileinfoID.Ctor);
        assert(jinfo != NULL);
        copyInfoOut(jinfo, info);

        jres = res;

        jret = (*env)->CallIntMethod(env, fuseSt.fsObj, fuseSt.fsID.flush_post, jpath,
                jinfo, jres);
        assert(jret != -1);

        copyStringIn(&_path, jpath);
        copyInfoIn(info, jinfo);
        res = jres;

        if (jpath != NULL) (*env)->DeleteLocalRef(env, jpath);
        if (jinfo != NULL) (*env)->DeleteLocalRef(env, jinfo);
    }

    // Cleanup
    free(_path);
    release_env(env);

    return 0;
}

/*
 * Release an open file when there are no more references to an open file: all
 * file descriptors are closed and all memory mappings are unmapped. The
 * return value of release is ignored.
 */
static int javafuse_release(const char *path, struct fuse_file_info *info)
{
    if (DEBUG) {
        PRINT_FUNC_ENTER;
    }

    // Initialization
    int res = 0;
    char *_path = strdup(path);
    assert(_path);

    jstring jpath = NULL;
    jobject jinfo = NULL;
    jint jret;
    jint jres;

    JNIEnv *env = get_env();

    // Pre Java Call
    if (PRE_CALL) {
        jpath = (*env)->NewStringUTF(env, _path);
        assert(jpath != NULL);

        jinfo = (*env)->NewObject(env, fuseSt.fileinfoClass, fuseSt.fileinfoID.Ctor);
        assert(jinfo != NULL);
        copyInfoOut(jinfo, info);

        jret = (*env)->CallIntMethod(env, fuseSt.fsObj, fuseSt.fsID.release_pre, jpath,
                jinfo);
        assert(jret != -1);

        copyStringIn(&_path, jpath);
        copyInfoIn(info, jinfo);

        if (jpath != NULL) (*env)->DeleteLocalRef(env, jpath);
        if (jinfo != NULL) (*env)->DeleteLocalRef(env, jinfo);
    }

    // Sys Call
    if (SYS_CALL) {
        res = close(info->fh);
        if (res == -1) {
            free(_path);
            release_env(env);
            return -errno;
        }
    }

    // Post Java Call
    if (POST_CALL) {
        jpath = (*env)->NewStringUTF(env, _path);
        assert(jpath != NULL);

        jinfo = (*env)->NewObject(env, fuseSt.fileinfoClass, fuseSt.fileinfoID.Ctor);
        assert(jinfo != NULL);
        copyInfoOut(jinfo, info);

        jres = res;

        jret = (*env)->CallIntMethod(env, fuseSt.fsObj, fuseSt.fsID.release_post, jpath,
                jinfo, jres);
        assert(jret != -1);

        copyStringIn(&_path, jpath);
        copyInfoIn(info, jinfo);
        res = jres;

        if (jpath != NULL) (*env)->DeleteLocalRef(env, jpath);
        if (jinfo != NULL) (*env)->DeleteLocalRef(env, jinfo);
    }

    // Cleanup
    free(_path);
    release_env(env);

    return 0;
}

/*
 * Standard fsync, but if the datasync parameter is non-zero then only the
 * user data should be flushed, not the meta-data.
 */
static int javafuse_fsync(const char *path, int datasync, struct fuse_file_info *info)
{
    if (DEBUG) {
        PRINT_FUNC_ENTER;
    }

    // Initialization
    int res = 0;
    char *_path = strdup(path);
    assert(_path);

    jstring jpath = NULL;
    jint jdatasync;
    jobject jinfo = NULL;
    jint jret;
    jint jres;

    JNIEnv *env = get_env();

    // Pre Java Call
    if (PRE_CALL) {
        jpath = (*env)->NewStringUTF(env, _path);
        assert(jpath != NULL);

        jdatasync = datasync;

        jinfo = (*env)->NewObject(env, fuseSt.fileinfoClass, fuseSt.fileinfoID.Ctor);
        assert(jinfo != NULL);
        copyInfoOut(jinfo, info);

        jret = (*env)->CallIntMethod(env, fuseSt.fsObj, fuseSt.fsID.fsync_pre, jpath,
                jdatasync, jinfo);
        assert(jret != -1);

        copyStringIn(&_path, jpath);
        datasync = jdatasync;
        copyInfoIn(info, jinfo);

        if (jpath != NULL) (*env)->DeleteLocalRef(env, jpath);
        if (jinfo != NULL) (*env)->DeleteLocalRef(env, jinfo);
    }

    // Sys Call
    if (SYS_CALL) {
        if (datasync)
            res = fdatasync(info->fh);
        else
            res = fsync(info->fh);

        if (res == -1) {
            free(_path);
            release_env(env);
            return -errno;
        }
    }

    // Post Java Call
    if (POST_CALL) {
        jpath = (*env)->NewStringUTF(env, _path);
        assert(jpath != NULL);

        jdatasync = datasync;

        jinfo = (*env)->NewObject(env, fuseSt.fileinfoClass, fuseSt.fileinfoID.Ctor);
        assert(jinfo != NULL);
        copyInfoOut(jinfo, info);

        jres = res;

        jret = (*env)->CallIntMethod(env, fuseSt.fsObj, fuseSt.fsID.fsync_post, jpath,
                jdatasync, jinfo, jres);
        assert(jret != -1);

        copyStringIn(&_path, jpath);
        datasync = jdatasync;
        copyInfoIn(info, jinfo);
        res = jres;

        if (jpath != NULL) (*env)->DeleteLocalRef(env, jpath);
        if (jinfo != NULL) (*env)->DeleteLocalRef(env, jinfo);
    }

    // Cleanup
    free(_path);
    release_env(env);

    return 0;
}

static int javafuse_setxattr(const char *path, const char *name, const char *value,
        size_t size, int flags)
{
    if (DEBUG) {
        PRINT_FUNC_ENTER;
    }

    // Initialization
    int res = 0;
    char *_path = strdup(path);
    assert(_path);
    char *_name = strdup(name);
    assert(_name);
    char *_value = strdup(value);
    assert(_value);

    jstring jpath = NULL;
    jstring jname = NULL;
    jstring jvalue = NULL;
    jint jsize;
    jint jflags;
    jint jret;
    jint jres;

    JNIEnv *env = get_env();

    // Pre Java Call
    if (PRE_CALL) {
        jpath = (*env)->NewStringUTF(env, _path);
        assert(jpath != NULL);

        jname = (*env)->NewStringUTF(env, _name);
        assert(jname != NULL);

        jvalue = (*env)->NewStringUTF(env, _value);
        assert(jvalue != NULL);

        jsize = size;
        jflags = flags;

        jret = (*env)->CallIntMethod(env, fuseSt.fsObj, fuseSt.fsID.setxattr_pre, jpath, jname,
                jvalue, jsize, jflags);
        assert(jret != -1);

        copyStringIn(&_path, jpath);
        copyStringIn(&_name, jname);
        copyStringIn(&_value, jvalue);
        size = jsize;
        flags = jflags;

        if (jpath != NULL) (*env)->DeleteLocalRef(env, jpath);
        if (jname != NULL) (*env)->DeleteLocalRef(env, jname);
        if (jvalue != NULL) (*env)->DeleteLocalRef(env, jvalue);
    }

    // Sys Call
    if (SYS_CALL) {
        res = lsetxattr(_path, _name, _value, size, flags); 
        if (res == -1) {
            free(_path);
            free(_name);
            free(_value);
            release_env(env);
            return -errno;
        }
    }

    // Post Java Call
    if (POST_CALL) {
        jpath = (*env)->NewStringUTF(env, _path);
        assert(jpath != NULL);

        jname = (*env)->NewStringUTF(env, _name);
        assert(jname != NULL);

        jvalue = (*env)->NewStringUTF(env, _value);
        assert(jvalue != NULL);

        jsize = size;
        jflags = flags;
        jres = res;

        jret = (*env)->CallIntMethod(env, fuseSt.fsObj, fuseSt.fsID.setxattr_post, jpath, jname,
                jvalue, jsize, jflags, jres);
        assert(jret != -1);

        copyStringIn(&_path, jpath);
        copyStringIn(&_name, jname);
        copyStringIn(&_value, jvalue);
        size = jsize;
        flags = jflags;
        res = jres;

        if (jpath != NULL) (*env)->DeleteLocalRef(env, jpath);
        if (jname != NULL) (*env)->DeleteLocalRef(env, jname);
        if (jvalue != NULL) (*env)->DeleteLocalRef(env, jvalue);
    }

    // Cleanup
    free(_path);
    free(_name);
    free(_value);
    release_env(env);

    return 0; 
}

/*
 * Can't pass value to the java code since it is uninitialized and we don't
 * know it's size.
 */
static int javafuse_getxattr(const char *path, const char *name, char *value, size_t
        size)
{
    if (DEBUG) {
        PRINT_FUNC_ENTER;
    }

    // Initialization
    int res = 0;
    char *_path = strdup(path);
    assert(_path);
    char *_name = strdup(name);
    assert(_name);

    //    char *_value = strdup((const char *)value);
    jstring jpath = NULL;
    jstring jname = NULL;
    jstring jvalue = NULL;
    jint jsize;
    jint jret;
    jint jres;

    JNIEnv *env = get_env();

    // Pre Java Call
    if (PRE_CALL) {
        jpath = (*env)->NewStringUTF(env, _path);
        assert(jpath != NULL);

        jname = (*env)->NewStringUTF(env, _name);
        assert(jname != NULL);

        jvalue = (*env)->NewStringUTF(env, "");
        assert(jvalue != NULL);

        jsize = size;

        jret = (*env)->CallIntMethod(env, fuseSt.fsObj, fuseSt.fsID.getxattr_pre, jpath, jname,
                jvalue, jsize);
        assert(jret != -1);

        copyStringIn(&_path, jpath);
        copyStringIn(&_name, jname);
        //copyStringIn(&_value, jvalue);
        size = jsize;

        if (jpath != NULL) (*env)->DeleteLocalRef(env, jpath);
        if (jname != NULL) (*env)->DeleteLocalRef(env, jname);
        if (jvalue != NULL) (*env)->DeleteLocalRef(env, jvalue);
    }

    // Sys Call
    if (SYS_CALL) {
        res = lgetxattr(_path, _name, value, size); 
        if (res == -1) {
            free(_path);
            free(_name);
            release_env(env);
            //free(_value);
            return -errno;
        }
    }

    // Post Java Call
    if (POST_CALL) {
        jpath = (*env)->NewStringUTF(env, _path);
        assert(jpath != NULL);

        jname = (*env)->NewStringUTF(env, _name);
        assert(jname != NULL);

        jvalue = (*env)->NewStringUTF(env, "");
        assert(jvalue != NULL);

        jsize = size;
        jres = res;

        jret = (*env)->CallIntMethod(env, fuseSt.fsObj, fuseSt.fsID.getxattr_post, jpath, jname,
                jvalue, jsize, jres);
        assert(jret != -1);

        copyStringIn(&_path, jpath);
        copyStringIn(&_name, jname);
        //copyStringIn(&_value, jvalue);
        size = jsize;
        res = jres;

        if (jpath != NULL) (*env)->DeleteLocalRef(env, jpath);
        if (jname != NULL) (*env)->DeleteLocalRef(env, jname);
        if (jvalue != NULL) (*env)->DeleteLocalRef(env, jvalue);
    }

    // Cleanup
    free(_path);
    free(_name);
    release_env(env);
    //    free(_value);

    return res;
}

static int javafuse_listxattr(const char *path, char *list, size_t size)
{
    if (DEBUG) {
        PRINT_FUNC_ENTER;
    }

    // Initialization
    int res = 0;
    char *_path = strdup(path);
    assert(_path);
    char *_list = strdup(list);
    assert(_list);

    jstring jpath = NULL;
    jstring jlist = NULL;
    jint jsize;
    jint jret;
    jint jres;

    JNIEnv *env = get_env();

    // Pre Java Call
    if (PRE_CALL) {
        jpath = (*env)->NewStringUTF(env, _path);
        assert(jpath != NULL);

        jlist = (*env)->NewStringUTF(env, _list);
        assert(jlist != NULL);

        jsize = size;

        jret = (*env)->CallIntMethod(env, fuseSt.fsObj, fuseSt.fsID.listxattr_pre, jpath, jlist,
                jsize);
        assert(jret != -1);

        copyStringIn(&_path, jpath);
        copyStringIn(&_list, jlist);
        size = jsize;

        if (jpath != NULL) (*env)->DeleteLocalRef(env, jpath);
        if (jlist != NULL) (*env)->DeleteLocalRef(env, jlist);
    }

    // Sys Call
    if (SYS_CALL) {
        res = llistxattr(_path, _list, size); 
        if (res == -1) {
            free(_path);
            free(_list);
            release_env(env);
            return -errno;
        }
    }

    // Post Java Call
    if (POST_CALL) {
        jpath = (*env)->NewStringUTF(env, _path);
        assert(jpath != NULL);

        jlist = (*env)->NewStringUTF(env, _list);
        assert(jlist != NULL);

        jsize = size;
        jres = res;

        jret = (*env)->CallIntMethod(env, fuseSt.fsObj, fuseSt.fsID.listxattr_post, jpath, jlist,
                jsize, jres);
        assert(jret != -1);

        copyStringIn(&_path, jpath);
        copyStringIn(&_list, jlist);
        size = jsize;
        res = jres;

        if (jpath != NULL) (*env)->DeleteLocalRef(env, jpath);
        if (jlist != NULL) (*env)->DeleteLocalRef(env, jlist);
    }

    // Cleanup
    free(_path);
    free(_list);
    release_env(env);

    return res;
}

static int javafuse_removexattr(const char *path, const char *name)
{
    if (DEBUG) {
        PRINT_FUNC_ENTER;
    }

    // Initialization
    int res = 0;
    char *_path = strdup(path);
    assert(_path);

    char *_name = strdup(name);
    assert(_name);

    jstring jpath = NULL;
    jstring jname = NULL;
    jint jret;
    jint jres;

    JNIEnv *env = get_env();

    // Pre Java Call
    if (PRE_CALL) {
        jpath = (*env)->NewStringUTF(env, _path);
        assert(jpath != NULL);

        jname = (*env)->NewStringUTF(env, _name);
        assert(jname != NULL);

        jret = (*env)->CallIntMethod(env, fuseSt.fsObj, fuseSt.fsID.removexattr_pre, jpath, jname);
        assert(jret != -1);

        copyStringIn(&_path, jpath);
        copyStringIn(&_name, jname);

        if (jpath != NULL) (*env)->DeleteLocalRef(env, jpath);
        if (jname != NULL) (*env)->DeleteLocalRef(env, jname);
    }

    // Sys Call
    if (SYS_CALL) {
        res = removexattr(_path, _name); 
        if (res == -1) {
            free(_path);
            free(_name);
            release_env(env);
            return -errno;
        }
    }

    // Post Java Call
    if (POST_CALL) {
        jpath = (*env)->NewStringUTF(env, _path);
        assert(jpath != NULL);

        jname = (*env)->NewStringUTF(env, _name);
        assert(jname != NULL);

        jres = res;

        jret = (*env)->CallIntMethod(env, fuseSt.fsObj, fuseSt.fsID.removexattr_post, jpath, jname, jres);
        assert(jret != -1);

        copyStringIn(&_path, jpath);
        copyStringIn(&_name, jname);
        res = jres;

        if (jpath != NULL) (*env)->DeleteLocalRef(env, jpath);
        if (jname != NULL) (*env)->DeleteLocalRef(env, jname);
    }

    // Cleanup
    free(_path);
    free(_name);
    release_env(env);

    return 0;
}

static int javafuse_opendir(const char *path, struct fuse_file_info *info)
{
    if (DEBUG) {
        PRINT_FUNC_ENTER;
    }

    // Initialization
    int res = 0;
    struct javafuse_dirp *d;
    char *_path = strdup(path);
    assert(_path);

    jstring jpath = NULL;
    jobject jinfo = NULL;
    jint jret;
    jint jres;

    JNIEnv *env = get_env();

    // Pre Java Call
    if (PRE_CALL) {
        jpath = (*env)->NewStringUTF(env, _path);
        assert(jpath != NULL);

        jinfo = (*env)->NewObject(env, fuseSt.fileinfoClass, fuseSt.fileinfoID.Ctor);
        assert(jinfo != NULL);
        copyInfoOut(jinfo, info);

        jret = (*env)->CallIntMethod(env, fuseSt.fsObj, fuseSt.fsID.opendir_pre, jpath,
                jinfo);
        assert(jret != -1);

        copyStringIn(&_path, jpath);
        copyInfoIn(info, jinfo);

        if (jpath != NULL) (*env)->DeleteLocalRef(env, jpath);
        if (jinfo != NULL) (*env)->DeleteLocalRef(env, jinfo);
    }

    // Sys Call
    if (SYS_CALL) {
        d = malloc(sizeof(struct javafuse_dirp));
        if (d == NULL) {
            free(_path);
            release_env(env);
		    return -ENOMEM;
        }

        d->dp = opendir(path);
	    if (d->dp == NULL) {
            free(_path);
            release_env(env);
    		free(d);
	    	return -errno;
    	}
	    d->offset = 0;
    	d->entry = NULL;

	    info->fh = (unsigned long) d;
    }

    // Post Java Call
    if (POST_CALL) {
        jpath = (*env)->NewStringUTF(env, _path);
        assert(jpath != NULL);

        jinfo = (*env)->NewObject(env, fuseSt.fileinfoClass, fuseSt.fileinfoID.Ctor);
        assert(jinfo != NULL);
        copyInfoOut(jinfo, info);

        jres = res;

        jret = (*env)->CallIntMethod(env, fuseSt.fsObj, fuseSt.fsID.opendir_post, jpath,
                jinfo, jres);
        assert(jret != -1);

        copyStringIn(&_path, jpath);
        copyInfoIn(info, jinfo);
        res = jres;

        if (jpath != NULL) (*env)->DeleteLocalRef(env, jpath);
        if (jinfo != NULL) (*env)->DeleteLocalRef(env, jinfo);
    }

    // Cleanup
    free(_path);
    release_env(env);

    return 0;
}

/*
 * Helper function to get javafuse_dirp* from fuse_file_info*
 * Adapted from fuse example fs.
 */
static inline struct javafuse_dirp *get_dirp(struct fuse_file_info *info)
{
    return (struct javafuse_dirp *) (uintptr_t) info->fh;
}

/*
 * This doesn't call the readdir() sys call but has to populate the buffer
 * manually with the directory entries. Can't pass the pointer to filler to
 * the java code since java can't access it. Can't pass the buffer to the Java
 * code since we don't have the size. So for the above just pass the
 * addresses.
 */
static int javafuse_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t
        offset, struct fuse_file_info *info)
{
    if (DEBUG) {
        PRINT_FUNC_ENTER;
    }

    // Initialization
    int res = 0;
    struct javafuse_dirp *d; 
    char *_path = strdup(path);
    assert(_path);

    jstring jpath = NULL;
    jlong jbuf;
    jlong jfiller;
    jint joffset;
    jobject jinfo = NULL;
    jint jret;
    jint jres;

    JNIEnv *env = get_env();

    // Pre Java Call
    if (PRE_CALL) {
        jpath = (*env)->NewStringUTF(env, _path);
        assert(jpath != NULL);

        jlong jbuf = (jlong) buf;
        jlong jfiller = (jlong) filler;
        jint joffset = offset;

        jinfo = (*env)->NewObject(env, fuseSt.fileinfoClass, fuseSt.fileinfoID.Ctor);
        assert(jinfo != NULL);
        copyInfoOut(jinfo, info);

        jint jret = (*env)->CallIntMethod(env, fuseSt.fsObj, fuseSt.fsID.readdir_pre, jpath, 
                jbuf, jfiller, joffset, jinfo);
        assert(jret != -1);

        copyStringIn(&_path, jpath);
        buf = (void *) jbuf;
        filler = (fuse_fill_dir_t) jfiller;
        offset = joffset;
        copyInfoIn(info, jinfo);

        if (jpath != NULL) (*env)->DeleteLocalRef(env, jpath);
        if (jinfo != NULL) (*env)->DeleteLocalRef(env, jinfo);
    }

    // System Call
    if (SYS_CALL) {
        d = get_dirp(info);

        if (offset != d->offset) {
            seekdir(d->dp, offset);
            d->entry = NULL;
            d->offset = offset;
        }

        // Traverse though the directory entries.
        while (1) {
            struct stat st;
            off_t nextoff;

            if (!d->entry) {
                d->entry = readdir(d->dp);
                if (!d->entry)
                    break;
            }

            memset(&st, 0, sizeof(st));
            st.st_ino = d->entry->d_ino;
            st.st_mode = d->entry->d_type << 12;
            nextoff = telldir(d->dp);

            // Fill the buf with this directory entry, but break if buf is full.
            if (filler(buf, d->entry->d_name, &st, nextoff))
                break;

            d->entry = NULL;
            d->offset = nextoff;
        }
    }

    // Post Java Call
    if (POST_CALL) {
        jpath = (*env)->NewStringUTF(env, _path);
        assert(jpath != NULL);

        jbuf = (jlong) buf;
        jfiller = (jlong) filler;
        joffset = offset;

        jinfo = (*env)->NewObject(env, fuseSt.fileinfoClass, fuseSt.fileinfoID.Ctor);
        assert(jinfo != NULL);
        copyInfoOut(jinfo, info);

        jres = res;

        jret = (*env)->CallIntMethod(env, fuseSt.fsObj, fuseSt.fsID.readdir_post, jpath, 
                jbuf, jfiller, joffset, jinfo, jres);
        assert(jret != -1);

        copyStringIn(&_path, jpath);
        buf = (void *) jbuf;
        filler = (fuse_fill_dir_t) jfiller;
        offset = joffset;
        copyInfoIn(info, jinfo);
        res = jres;

        if (jpath != NULL) (*env)->DeleteLocalRef(env, jpath);
        if (jinfo != NULL) (*env)->DeleteLocalRef(env, jinfo);
    }

    // Cleanup
    free(_path);
    release_env(env);

    return 0;
}

/*
 * Release a directory.
 */
static int javafuse_releasedir(const char *path, struct fuse_file_info *info)
{
    if (DEBUG) {
        PRINT_FUNC_ENTER;
    }

    // Initialization
    int res = 0;
    char *_path = strdup(path);
    assert(_path);

    DIR *dp;
    jstring jpath = NULL;
    jobject jinfo = NULL;
    jint jret;
    jint jres;

    JNIEnv *env = get_env();

    // Pre Java Call
    if (PRE_CALL) {
        jpath = (*env)->NewStringUTF(env, _path);
        assert(jpath != NULL);

        jinfo = (*env)->NewObject(env, fuseSt.fileinfoClass, fuseSt.fileinfoID.Ctor);
        assert(jinfo != NULL);
        copyInfoOut(jinfo, info);

        jret = (*env)->CallIntMethod(env, fuseSt.fsObj, fuseSt.fsID.releasedir_pre, jpath,
                jinfo);
        assert(jret != -1);

        copyStringIn(&_path, jpath);
        copyInfoIn(info, jinfo);

        if (jpath != NULL) (*env)->DeleteLocalRef(env, jpath);
        if (jinfo != NULL) (*env)->DeleteLocalRef(env, jinfo);
    }

    // Sys Call
    if (SYS_CALL) {
        dp = get_dirp(info);
        closedir(dp);
    }

    // Post Java Call
    if (POST_CALL) {
        jpath = (*env)->NewStringUTF(env, _path);
        assert(jpath != NULL);

        jinfo = (*env)->NewObject(env, fuseSt.fileinfoClass, fuseSt.fileinfoID.Ctor);
        assert(jinfo != NULL);
        copyInfoOut(jinfo, info);

        jres = res;

        jret = (*env)->CallIntMethod(env, fuseSt.fsObj, fuseSt.fsID.releasedir_post, jpath,
                jinfo, jres);
        assert(jret != -1);

        copyStringIn(&_path, jpath);
        copyInfoIn(info, jinfo);
        res = jres;

        if (jpath != NULL) (*env)->DeleteLocalRef(env, jpath);
        if (jinfo != NULL) (*env)->DeleteLocalRef(env, jinfo);
    }

    // Cleanup
    free(_path);
    release_env(env);

    return 0;
}

/*
 * Synchronize directory contents. If datasync parameter is non-zero, then
 * only the user data and not the meta-data should be flushed.
 */
static int javafuse_fsyncdir(const char *path, int datasync, struct fuse_file_info
        *info)
{
    if (DEBUG) {
        PRINT_FUNC_ENTER;
    }

    // Initialization
    int res = 0;
    int fd = 0;
    char *_path = strdup(path);
    assert(_path);

    DIR *dp;
    struct dirent *de;
    jstring jpath = NULL;
    jint jdatasync;
    jobject jinfo = NULL;
    jint jret;
    jint jres;

    JNIEnv *env = get_env();

    // Pre Java Call
    if (PRE_CALL) {
        jpath = (*env)->NewStringUTF(env, _path);
        assert(jpath != NULL);

        jdatasync = datasync;

        jinfo = (*env)->NewObject(env, fuseSt.fileinfoClass, fuseSt.fileinfoID.Ctor);
        assert(jinfo != NULL);
        copyInfoOut(jinfo, info);

        jret = (*env)->CallIntMethod(env, fuseSt.fsObj, fuseSt.fsID.fsyncdir_pre, jpath,
                jdatasync, jinfo);
        assert(jret != -1);

        copyStringIn(&_path, jpath);
        datasync = jdatasync;
        copyInfoIn(info, jinfo);

        if (jpath != NULL) (*env)->DeleteLocalRef(env, jpath);
        if (jinfo != NULL) (*env)->DeleteLocalRef(env, jinfo);
    }

    // Sys Call
    if (SYS_CALL) {

        // Call fsync on each file in directory.
        dp = get_dirp(info);
        seekdir(dp, 0);

        // Traverse though the directory entries.
        while ((de = readdir(dp)) != NULL) {
            fd =  open(de->d_name, O_RDONLY);
            if (fd == -1) {
                free(_path);
                return -errno;
            }

            if (datasync)
                res = fdatasync(info->fh);
            else
                res = fsync(info->fh);

            if (res == -1) {
                close(fd);
                free(_path);
                return -errno;
            }
            close(fd);
        }
    }

    // Post Java Call
    if (POST_CALL) {
        jpath = (*env)->NewStringUTF(env, _path);
        assert(jpath != NULL);

        jdatasync = datasync;

        jinfo = (*env)->NewObject(env, fuseSt.fileinfoClass, fuseSt.fileinfoID.Ctor);
        assert(jinfo != NULL);
        copyInfoOut(jinfo, info);

        jres = res;

        jret = (*env)->CallIntMethod(env, fuseSt.fsObj, fuseSt.fsID.fsyncdir_post, jpath,
                jdatasync, jinfo, jres);
        assert(jret != -1);

        copyStringIn(&_path, jpath);
        datasync = jdatasync;
        copyInfoIn(info, jinfo);
        res = jres;

        if (jpath != NULL) (*env)->DeleteLocalRef(env, jpath);
        if (jinfo != NULL) (*env)->DeleteLocalRef(env, jinfo);
    }

    // Cleanup
    free(_path);
    release_env(env);

    return 0;
}

static void* javafuse_init(struct fuse_conn_info *conn)
{
    if (DEBUG) {
        PRINT_FUNC_ENTER;
    }

    JNIEnv *env = get_env();

    // Initialize classes.
    init_fsClass(classname);
    init_contextClass();
    init_statClass();
    init_statvfsClass();
    init_fileinfoClass();
    init_conninfoClass();
    init_utimbufClass();

    // Change default permissions for files.
    umask(0);

    release_env(env);

    return NULL;
}

static void javafuse_destroy(void *arg)
{
    if (DEBUG) {
        PRINT_FUNC_ENTER;
    }

    JNIEnv *env = get_env();

    /* Free all global references here. */

    if (fuseSt.contextClass != NULL)
        (*env)->DeleteGlobalRef(env, fuseSt.contextClass);

    if (fuseSt.statClass != NULL)
        (*env)->DeleteGlobalRef(env, fuseSt.statClass);

    if (fuseSt.statvfsClass != NULL)
        (*env)->DeleteGlobalRef(env, fuseSt.statvfsClass);

    if (fuseSt.fileinfoClass != NULL)
        (*env)->DeleteGlobalRef(env, fuseSt.fileinfoClass);

    if (fuseSt.conninfoClass != NULL)
        (*env)->DeleteGlobalRef(env, fuseSt.conninfoClass);

    if (fuseSt.utimbufClass != NULL)
        (*env)->DeleteGlobalRef(env, fuseSt.utimbufClass);

    // For the filesystem, call the finalize method as well if it's defined.
    if (fuseSt.fsObj != NULL) {
        if (fuseSt.fsID.finalize != NULL)
            (*env)->CallVoidMethod(env, fuseSt.fsObj, fuseSt.fsID.finalize);
        (*env)->DeleteGlobalRef(env, fuseSt.fsObj);
    }

    if (fuseSt.fsClass != NULL)
        (*env)->DeleteGlobalRef(env, fuseSt.fsClass);

    release_env(env);
}

static int javafuse_access(const char *path, int mode)
{
    if (DEBUG) {
        PRINT_FUNC_ENTER;
    }

    // Initialization
    int res = 0;
    char *_path = strdup(path);
    assert(_path);

    jstring jpath = NULL;
    jint jmode;
    jint jret;
    jint jres;

    JNIEnv *env = get_env();

    // Pre Java Call
    if (PRE_CALL) {
        jpath = (*env)->NewStringUTF(env, _path);
        assert(jpath != NULL);

        jmode = mode;
        jret = (*env)->CallIntMethod(env, fuseSt.fsObj, fuseSt.fsID.access_pre, jpath, jmode);
        assert(jret != -1);

        copyStringIn(&_path, jpath);
        mode = jmode;

        if (jpath != NULL) (*env)->DeleteLocalRef(env, jpath);
    }

    // Sys Call
    if (SYS_CALL) {
        res = access(_path, mode);
        if (res == -1) {
            free(_path);
            release_env(env);
            return -errno;
        }
    }

    // Post Java Call
    if (POST_CALL) {
        jpath = (*env)->NewStringUTF(env, _path);
        assert(jpath != NULL);

        jmode = mode;
        jres = res;

        jret = (*env)->CallIntMethod(env, fuseSt.fsObj, fuseSt.fsID.access_post, jpath, jmode, jres);
        assert(jret != -1);

        copyStringIn(&_path, jpath);
        mode = jmode;
        res = jres;

        if (jpath != NULL) (*env)->DeleteLocalRef(env, jpath);
    }

    // Cleanup
    free(_path);
    release_env(env);

    return 0;
}

/*
 * The creat() system call is equivalent to open() with flags equal to
 * O_REAT|O_WRONLY|O_TRUNC
 */
static int javafuse_create(const char *path, mode_t mode, struct fuse_file_info *info)
{
    if (DEBUG) {
        PRINT_FUNC_ENTER;
    }

    // Initialization
    int fd = 0;
    char *_path = strdup(path);
    assert(_path);

    jstring jpath = NULL;
    jint jmode;
    jobject jinfo = NULL;
    jint jret;
    jint jres;

    JNIEnv *env = get_env();

    // Pre Java Call
    if (PRE_CALL) {
        jpath = (*env)->NewStringUTF(env, _path);
        assert(jpath != NULL);

        jmode = mode;

        jinfo = (*env)->NewObject(env, fuseSt.fileinfoClass, fuseSt.fileinfoID.Ctor);
        assert(jinfo != NULL);
        copyInfoOut(jinfo, info);

        jret = (*env)->CallIntMethod(env, fuseSt.fsObj, fuseSt.fsID.create_pre, jpath,
                jmode, jinfo);
        assert(jret != -1);

        copyStringIn(&_path, jpath);
        mode = jmode;
        copyInfoIn(info, jinfo);

        if (jpath != NULL) (*env)->DeleteLocalRef(env, jpath);
        if (jinfo != NULL) (*env)->DeleteLocalRef(env, jinfo);
    }

    // Sys Call
    if (SYS_CALL) {
        fd = open(_path, info->flags, mode);
        if (fd == -1) {
            free (_path);
            release_env(env);
            return -errno;
        }
        info->fh = fd;
    }

    // Post Java Call
    if (POST_CALL) {
        jpath = (*env)->NewStringUTF(env, _path);
        assert(jpath != NULL);

        jmode = mode;

        jinfo = (*env)->NewObject(env, fuseSt.fileinfoClass, fuseSt.fileinfoID.Ctor);
        assert(jinfo != NULL);
        copyInfoOut(jinfo, info);

        jres = fd;

        jret = (*env)->CallIntMethod(env, fuseSt.fsObj, fuseSt.fsID.create_post, jpath,
                jmode, jinfo, jres);
        assert(jret != -1);

        copyStringIn(&_path, jpath);
        mode = jmode;
        copyInfoIn(info, jinfo);
        fd = jres;

        if (jpath != NULL) (*env)->DeleteLocalRef(env, jpath);
        if (jinfo != NULL) (*env)->DeleteLocalRef(env, jinfo);
    }

    // Cleanup
    free(_path);
    release_env(env);

    return 0;
}

static int javafuse_ftruncate(const char *path, off_t length, struct fuse_file_info
        *info)
{
    if (DEBUG) {
        PRINT_FUNC_ENTER;
    }

    // Initialization
    int res = 0;
    char *_path = strdup(path);
    assert(_path);

    jstring jpath = NULL;
    jint jlength;
    jobject jinfo = NULL;
    jint jret;
    jint jres;

    JNIEnv *env = get_env();

    // Pre Java Call
    if (PRE_CALL) {
        jpath = (*env)->NewStringUTF(env, _path);
        assert(jpath != NULL);

        jlength = length;

        jinfo = (*env)->NewObject(env, fuseSt.fileinfoClass, fuseSt.fileinfoID.Ctor);
        assert(jinfo != NULL);
        copyInfoOut(jinfo, info);

        jret = (*env)->CallIntMethod(env, fuseSt.fsObj, fuseSt.fsID.ftruncate_pre, jpath, jlength,
                jinfo);
        assert(jret != -1);

        copyStringIn(&_path, jpath);
        length = jlength;
        copyInfoIn(info, jinfo);

        if (jpath != NULL) (*env)->DeleteLocalRef(env, jpath);
        if (jinfo != NULL) (*env)->DeleteLocalRef(env, jinfo);
    }

    // Sys Call
    if (SYS_CALL) {
        res = ftruncate(info->fh, length);
        if (res == -1) {
            free(_path);
            release_env(env);
            return -errno;
        }
    }

    // Post Java Call
    if (POST_CALL) {
        jpath = (*env)->NewStringUTF(env, _path);
        assert(jpath != NULL);

        jlength = length;

        jinfo = (*env)->NewObject(env, fuseSt.fileinfoClass, fuseSt.fileinfoID.Ctor);
        assert(jinfo != NULL);
        copyInfoOut(jinfo, info);

        jres = res;

        jret = (*env)->CallIntMethod(env, fuseSt.fsObj, fuseSt.fsID.ftruncate_post, jpath, jlength,
                jinfo, jres);
        assert(jret != -1);

        copyStringIn(&_path, jpath);
        length = jlength;
        copyInfoIn(info, jinfo);
        res = jres;

        if (jpath != NULL) (*env)->DeleteLocalRef(env, jpath);
        if (jinfo != NULL) (*env)->DeleteLocalRef(env, jinfo);
    }

    // Cleanup
    free(_path);
    release_env(env);

    return 0;
}

static int javafuse_fgetattr(const char *path, struct stat *buf, struct fuse_file_info
        *info)
{
    if (DEBUG) {
        PRINT_FUNC_ENTER;
    }

    // Initialization
    int res = 0;
    char *_path = strdup(path);
    assert(_path);

    jstring jpath = NULL;
    jobject jbuf = NULL;
    jobject jinfo = NULL;
    jint jret;
    jint jres;

    JNIEnv *env = get_env();

    // Pre Java Call
    if (PRE_CALL) {
        jpath = (*env)->NewStringUTF(env, _path);
        assert(jpath != NULL);

        jbuf = (*env)->NewObject(env, fuseSt.statClass, fuseSt.statID.Ctor);
        assert(jbuf != NULL);
        copyStatOut(jbuf, buf);

        jinfo = (*env)->NewObject(env, fuseSt.fileinfoClass, fuseSt.fileinfoID.Ctor);
        assert(jinfo != NULL);
        copyInfoOut(jinfo, info);

        jret = (*env)->CallIntMethod(env, fuseSt.fsObj, fuseSt.fsID.fgetattr_pre, jpath, jbuf,
                jinfo);
        assert(jret != -1);

        copyStringIn(&_path, jpath);
        copyStatIn(buf, jbuf);
        copyInfoIn(info, jinfo);

        if (jpath != NULL) (*env)->DeleteLocalRef(env, jpath);
        if (jbuf != NULL) (*env)->DeleteLocalRef(env, jbuf);
        if (jinfo != NULL) (*env)->DeleteLocalRef(env, jinfo);
    }

    // Sys Call
    if (SYS_CALL) {
        res = fstat(info->fh, buf);
        if (res == -1) {
            free(_path);
            release_env(env);
            return -errno;
        }
    }

    // Post Java Call
    if (POST_CALL) {
        jpath = (*env)->NewStringUTF(env, _path);
        assert(jpath != NULL);

        jbuf = (*env)->NewObject(env, fuseSt.statClass, fuseSt.statID.Ctor);
        assert(jbuf != NULL);
        copyStatOut(jbuf, buf);

        jinfo = (*env)->NewObject(env, fuseSt.fileinfoClass, fuseSt.fileinfoID.Ctor);
        assert(jinfo != NULL);
        copyInfoOut(jinfo, info);

        jres = res;

        jret = (*env)->CallIntMethod(env, fuseSt.fsObj, fuseSt.fsID.fgetattr_post, jpath, jbuf,
                jinfo, jres);
        assert(jret != -1);

        copyStringIn(&_path, jpath);
        copyStatIn(buf, jbuf);
        copyInfoIn(info, jinfo);
        res = jres;

        if (jpath != NULL) (*env)->DeleteLocalRef(env, jpath);
        if (jbuf != NULL) (*env)->DeleteLocalRef(env, jbuf);
        if (jinfo != NULL) (*env)->DeleteLocalRef(env, jinfo);
    }

    // Cleanup
    free(_path); 
    release_env(env);

    return 0;
}

static int javafuse_lock(const char *path, struct fuse_file_info *info, int cmd, struct
        flock *lock)
{
    // STUB
    return 0;
}

static int javafuse_utimens(const char *path, const struct timespec tv[2])
{
    // STUB
    return 0;
}

static int javafuse_bmap(const char *path, size_t blocksize, uint64_t *idx)
{
    // STUB
    return 0;
}

static struct fuse_operations javafuse_oper = {
    .getattr    = javafuse_getattr,
    .readlink   = javafuse_readlink,
    .mknod      = javafuse_mknod,
    .mkdir      = javafuse_mkdir,
    .unlink     = javafuse_unlink,
    .rmdir      = javafuse_rmdir,
    .symlink    = javafuse_symlink,
    .rename     = javafuse_rename,
    .link       = javafuse_link,
    .chmod      = javafuse_chmod,
    .chown      = javafuse_chown,
    .truncate   = javafuse_truncate,
    .utime      = javafuse_utime,
    .open       = javafuse_open,
    .read       = javafuse_read,
    .write      = javafuse_write,
    .statfs     = javafuse_statfs,
    .flush      = javafuse_flush,
    .release    = javafuse_release,
    .fsync      = javafuse_fsync,
    .setxattr   = javafuse_setxattr,
    .getxattr   = javafuse_getxattr,
    .listxattr  = javafuse_listxattr,
    .removexattr    = javafuse_removexattr,
    .opendir    = javafuse_opendir,
    .readdir    = javafuse_readdir,
    .releasedir = javafuse_releasedir,
    .fsyncdir   = javafuse_fsyncdir,
    .init       = javafuse_init,
    .destroy    = javafuse_destroy,
    .access     = javafuse_access,
    .create     = javafuse_create,
    .ftruncate  = javafuse_ftruncate,
    .fgetattr   = javafuse_fgetattr,
    .lock       = javafuse_lock,
    .utimens    = javafuse_utimens,
    .bmap       = javafuse_bmap,
};

int main(int argc, char *argv[])
{
    int i;

    // Parse the command line.
    read_cmdline(argc, argv);

    // If user provided config file path then read it. Will overwrite command
    // line options!
    if (configfile != NULL)
        read_config(configfile);

    if (DEBUG) {
        printf("%s config file:\n", configfile);

        printf("%d cmdline fuse arguments:", fuseArgc);
        for (i = 0; i < fuseArgc; i++)
            printf(" %s", fuseArgv[i]);
        printf("\n");

        printf("%d cmdline java arguments:", javaArgc);
        for (i = 0; i < javaArgc; i++)
            printf(" %s", javaArgv[i]);
        printf("\n");
    }

    // Must have class name of Java FS.
    if (classname == NULL)
    {
        printf("Missing option: -CPackagename/ClassName\n");
        return -1;
    }

    // Initialize the JVM and the JNI stuff.
    init_JVM(javaArgc, javaArgv);

    return fuse_main(fuseArgc, fuseArgv, &javafuse_oper, NULL);
}

/*
 * Parse a configuratin file consisting of a space separated key-value pair on
 * each line. Comments begin with # and are ignored. Unrecognized keys are
 * ignored. Add keys below as needed.
 */
static void read_config(const char *path)
{
    char *buf = (char *) malloc(80 * sizeof(char));
    char *key = (char *) malloc(80 * sizeof(char));
    char *value = (char *) malloc(80 * sizeof(char));

    FILE *f = fopen(path, "r");
    assert(f != NULL);

    while (1) {
        fgets(buf, 80, f);
        if (feof(f))
            break;

        key = strtok(buf, " ");
        // Ignore comments
        if (key[0] == '#')
            continue;

        value = strtok(NULL, " ");

        if (strncmp(key, "CLASSNAME", strlen("CLASSNAME")) == 0)
            classname = strndup(value, strlen(value) - 1);
        else if (strncmp(key, "JVMARGS", strlen("JVMARGS")) == 0)
            javaArgv[javaArgc++] = strndup(value, strlen(value) - 1);
        else if (strncmp(key, "FUSEARGS", strlen("FUSEARGS")) == 0)
            fuseArgv[fuseArgc++] = strndup(value, strlen(value) - 1);
        else if (strncmp(key, "DEBUG", strlen("DEBUG")) == 0)
            DEBUG = atoi(value);
        else if (strncmp(key, "META_DATA_ONLY", strlen("META_DATA_ONLY")) == 0)
            META_DATA_ONLY = atoi(value);
        else if (strncmp(key, "PRE_CALL", strlen("PRE_CALL")) == 0)
            PRE_CALL = atoi(value);
        else if (strncmp(key, "POST_CALL", strlen("POST_CALL")) == 0)
            POST_CALL = atoi(value);
        else if (strncmp(key, "SYS_CALL", strlen("SYS_CALL")) == 0)
            SYS_CALL = atoi(value);
    }
}

/*
 * Parse the command line arguments. Code adapted from the fuse-j project.
 */
static void read_cmdline(int argc, char *argv[]) 
{
    int i;

    // split args into fuse & java args
    for (i = 0; i < argc; i++)
    {
        char *arg = argv[i];
        if (strncmp(arg, "-C", 2) == 0)
            classname = &(arg[2]);
        else if (strncmp(arg, "-F", 2) == 0)
            configfile = &(arg[2]);
        else if (strncmp(arg, "-D", 2) == 0)
            DEBUG = 1;
        else if (strncmp(arg, "-J", 2) == 0)
            javaArgv[javaArgc++] = &(arg[2]);
        else if (strncmp(arg, "-X", 2) == 0)
            PRE_CALL = 1;
        else if (strncmp(arg, "-Y", 2) == 0)
            POST_CALL = 1;
        else if (strncmp(arg, "-Z", 2) == 0)
            SYS_CALL = 1;
        else 
            fuseArgv[fuseArgc++] = arg;
    }
}
