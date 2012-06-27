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

#ifndef _DEFINE_H_
#define _DEFINE_H_

//#define FUSE_USE_VERSION 28
#define JNI_USE_VERSION JNI_VERSION_1_2

#define ERROR_MSG printf("Error at: %s : %s : %d\n", __FILE__, __func__, __LINE__);
//#define _XOPEN_SOURCE 500
#define _GNU_SOURCE
#define UID fuse_get_context()->uid
#define GID fuse_get_context()->gid
#define PATH_SEPARATOR ':'
#define USER_CLASSPATH "./build"

#define PRINT_FUNC_NAME printf("%s\n", __func__)
#define PRINT_FUNC_ENTER printf("Enter: %s\n", __func__)
#define PRINT_FUNC_EXIT printf("Exit: %s\n", __func__)

#endif
