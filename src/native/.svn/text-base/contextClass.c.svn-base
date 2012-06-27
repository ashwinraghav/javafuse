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

#include "contextClass.h"
#include "javafuse_jni.h"
#include "includes.h"

extern fuseStruct fuseSt;

/*
 * Initilize the fuse_context class.
 */
void init_contextClass()
{
    JNIEnv *env = get_env();

    jclass _contextClass = (*env)->FindClass(env, "javafuse/Fuse_context");
    fuseSt.contextClass = (*env)->NewGlobalRef(env, _contextClass);
    assert(fuseSt.contextClass != NULL);

    fuseSt.contextID.Ctor = (*env)->GetMethodID(env, fuseSt.contextClass, "<init>", "()V");
    assert(fuseSt.contextID.Ctor != NULL);

    fuseSt.contextID.finalize = (*env)->GetMethodID(env, fuseSt.contextClass, "finalize", "()V");
    assert(fuseSt.contextID.finalize != NULL);

    fuseSt.contextID.uid = (*env)->GetFieldID(env, fuseSt.contextClass, "uid", "J");
    assert(fuseSt.contextID.uid != NULL);
    fuseSt.contextID.gid = (*env)->GetFieldID(env, fuseSt.contextClass, "gid", "J");
    assert(fuseSt.contextID.gid != NULL);
    fuseSt.contextID.pid = (*env)->GetFieldID(env, fuseSt.contextClass, "pid", "J");
    assert(fuseSt.contextID.pid != NULL);
    fuseSt.contextID.private_data = (*env)->GetFieldID(env, fuseSt.contextClass, "private_data", "J");
    assert(fuseSt.contextID.private_data != NULL);

    release_env(env);
}

/*
 * Copy to fuse_context struct from fuse_context object.
 */
void copyContextIn(struct fuse_context *context, jobject jcontext)
{
    JNIEnv *env = get_env();

    context->uid = (*env)->GetLongField(env, jcontext, fuseSt.contextID.uid);
    context->gid = (*env)->GetLongField(env, jcontext, fuseSt.contextID.gid);
    context->pid = (*env)->GetLongField(env, jcontext, fuseSt.contextID.pid);
    context->private_data = (void *) (*env)->GetLongField(env, jcontext, fuseSt.contextID.private_data);

    release_env(env);
}

/*
 * Copy to fuse_context object from fuse_context struct.
 */
void copyContextOut(jobject jcontext, struct fuse_context *context)
{
    JNIEnv *env = get_env();

    (*env)->SetLongField(env, jcontext, fuseSt.contextID.uid, context->uid);
    (*env)->SetLongField(env, jcontext, fuseSt.contextID.gid, context->gid);
    (*env)->SetLongField(env, jcontext, fuseSt.contextID.pid, context->pid);
    (*env)->SetLongField(env, jcontext, fuseSt.contextID.private_data, (long) context->private_data);

    release_env(env);
}

/*
 * Copy to fuse_context object from fuse_context struct, when called from
 * Java.
 */
JNIEXPORT void JNICALL Java_javafuse_Fuse_1context_copyContextIn(JNIEnv *env, jobject jcontext)
{
    struct fuse_context *context = fuse_get_context();

    (*env)->SetLongField(env, jcontext, fuseSt.contextID.uid, context->uid);
    (*env)->SetLongField(env, jcontext, fuseSt.contextID.gid, context->gid);
    (*env)->SetLongField(env, jcontext, fuseSt.contextID.pid, context->pid);
    (*env)->SetLongField(env, jcontext, fuseSt.contextID.private_data, (long) context->private_data);
}
