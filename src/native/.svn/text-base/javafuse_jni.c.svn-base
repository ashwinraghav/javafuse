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

#include "javafuse_jni.h"
#include "define.h"
#include "includes.h"
#include <stdlib.h>
#include <string.h>

extern int errno;
fuseStruct fuseSt;

/*
 * Copies to C string from Java jstring. Allocates a new C string in the
 * process, as the size of the returned Java string may be different from that
 * of the original C string.
 */
void copyStringIn(char **path, jstring jpath)
{
    JNIEnv *env = get_env();

    int length = (int) (*env)->GetStringUTFLength(env, jpath);

    *path = realloc(*path, length * sizeof(char) + 1);
    assert(path != NULL);

    // We have to make a temporary buffer since the pointer returned by JNI
    // has to be freed. Also, we need to memcpy the result of
    // GetStringUTFChars since it may or may not be a copy of the original
    // (see wiki).
    char *temp = (char *) (*env)->GetStringUTFChars(env, jpath, NULL);
    assert(temp != NULL);

    memcpy(*path, temp, length + 1);
    (*env)->ReleaseStringUTFChars(env, jpath, temp);

    release_env(env);
}

/*
 * Copies to C buffer count bytes from Java byte array.
 */
void copyByteArrayIn(char **buf, jbyteArray jbuf, int count)
{
    JNIEnv *env = get_env();

    //int length = (int) (*env)->GetArrayLength(env, jbuf);

    //*buf = realloc(*buf, length * sizeof(char));
    //assert(*buf != NULL);

    (*env)->GetByteArrayRegion(env, jbuf, 0, count, (jbyte *)*buf);

    release_env(env);
}

/*
 * Attach the current thread to the JVM. Code adapted from the FUSE-J project.
 */
JNIEnv* get_env()
{
   JNIEnv *env;
   //JavaVMAttachArgs args;

   //args.version = JNI_USE_VERSION;
   // args.name = NULL;
   // args.group = threadGroup;

   // A GCJ 4.0 bug workarround (supplied by Alexander Boström <abo@stacken.kth.se>).
   //if ((*fuseSt.jvm)->GetEnv(fuseSt.jvm, (void**)&env, args.version) == JNI_OK)
   //   return env;

   // TRACE("will attach thread");

   // Attach thread as daemon thread so that JVM can exit after unmounting the fuseFS.
   jint jres = (*fuseSt.jvm)->AttachCurrentThreadAsDaemon(fuseSt.jvm, (void**)&env, &fuseSt.jvmArgs);
   assert(jres == 0);

   // TRACE("did attach thread to env: %p", env);

   return env;
}

/*
 * Detach the current thread from the JVM. Code adapted from the FUSE-J project.
 */
void release_env(JNIEnv *env)
{
    /*
   if (env == mainEnv)
   {
      // TRACE("will NOT detach main thread from env: %p", env);
   }
   else
   {
      // TRACE("will NOT detach thread from env: %p", env);

      // Currently native threads are attached to JVM as daemon threads so we don't need to
      // detach them at return from a Java method call. It is in fact beter not to detach them
      // since then every new Java call would need to atach new Java Thread until max. number of
      // Java threads is exhausted.
      //
      //TRACE("will detach thread from env: %p", env);
      //(*fuseSt.jvm)->DetachCurrentThread(fuseSt.jvm);
      //TRACE("did detach thread");
   }
   */
}

/*
 * Initialize the Java VM.
 */
void init_JVM(int argc, char *argv[])
{
#ifdef JNI_VERSION_1_2
    // Set up JVM parameters
    JNIEnv *env;
    JavaVMInitArgs vm_args;
    int n = argc + 3;
    int i = 0;
    JavaVMOption options[n];

    // Set user supplied JVM options.
    for (i = 0; i < argc; i++) {
        options[i].optionString = argv[i];
    }
    
    // Set default JVM options.
    options[i++].optionString = "-Djava.class.path=.:build:fs/build";
    options[i++].optionString = "-Xint";
    options[i++].optionString = "-Xcheck:jni";

    vm_args.version = 0x00010002;
    vm_args.options = options;
    vm_args.nOptions = n;
    vm_args.ignoreUnrecognized = JNI_TRUE;

    /* Create the Java VM */
    jint res = JNI_CreateJavaVM(&fuseSt.jvm, (void**)&env, &vm_args);
#else
    fprintf(stderr, "Require JNI version 1.2\n");
    exit(1);
#endif
    if (res < 0) {
        fprintf(stderr, "Can't create Java VM\n");
        exit(1);
    }

    fuseSt.jvmArgs.version = JNI_USE_VERSION;
}
