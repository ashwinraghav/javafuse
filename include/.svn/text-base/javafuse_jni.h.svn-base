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

#ifndef _JAVAFUSE_JNI_H_
#define _JAVAFUSE_JNI_H_

#include "fsClass.h"
#include "contextClass.h"
#include "statClass.h"
#include "statvfsClass.h"
#include "fileinfoClass.h"
#include "conninfoClass.h"
#include "utimbufClass.h"
#include "includes.h"

typedef struct
{
    JavaVM *jvm;
    JavaVMAttachArgs jvmArgs;

    // For each class, we need a global reference to the class, and a 
    // structure that contains field and method IDs for the class.
    
    jclass fsClass;
    jobject fsObj;
    fsClassID fsID;

    jclass contextClass;
    contextClassID contextID;

    jclass statClass;
    statClassID statID;

    jclass statvfsClass;
    statvfsClassID statvfsID;

    jclass fileinfoClass;    
    fileinfoClassID fileinfoID;

    jclass conninfoClass;    
    conninfoClassID conninfoID;

    jclass utimbufClass;
    utimbufClassID utimbufID;
} fuseStruct;

void copyStringIn(char **path, jstring jpath);
void copyByteArrayIn(char **buf, jbyteArray jbuf, int count);

JNIEnv* get_env();
void release_env(JNIEnv *env);

void init_JVM(int argc, char *argv[]);

#endif
