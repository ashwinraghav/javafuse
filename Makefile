include build.conf

srcdir = src/native
javadir = src/java
includedir = include
builddir = build
fsdir = fs # Directory for user filesystems.
utildir = util
executable = javafuse
library = libjavafuse.so

CC = gcc
CFLAGS = -g -Wall `pkg-config --cflags fuse` -D_FILE_OFFSET_BITS=64 -D_DARWIN_USE_64_BIT_INODE
LDFLAGS = `pkg-config --libs fuse` $(shell java -jar util/DumpJVMLdPath.jar) -ljvm -L$(builddir) -ljavafuse
JAVAC = javac
JAVA = java
JFLAGS = -Xlint -source 5

INCLUDES = -I/usr/local/lib/ -I$(includedir) -I$(JDK_HOME)/include -I/System/Library/Frameworks/JavaVM.framework/Headers 

#INCLUDES = -I$(includedir) -I$(JDK_HOME)/include -I$(JDK_HOME)/include/linux -I/System/Library/Frameworks/JavaVM.framework/Headers -I/usr/local/lib/pkgconfig/
CLASSPATH = $(builddir)

vpath %.c $(srcdir)
vpath %.h $(includedir) .
vpath %.o $(builddir)
vpath %.java $(javadir) $(fsdir)

sources = $(shell find $(srcdir) -type f -name '*.c')
deps = $(sources:$(srcdir)/%.c=$(builddir)/%.dep)
objects = $(sources:$(srcdir)/%.c=$(builddir)/%.o)

java_sources = $(shell find $(javadir) -type f -name '*.java')
java_classes = $(java_sources:$(javadir)/%.java=$(builddir)/javafuse/%.class)

fs_sources = $(shell find $(fsdir) -type f -name 'JavaFS.java')
fs_classes = $(fs_sources:fs/%.java=$(builddir)/javafuse/%.class)

.PHONY: clean all

all: $(builddir) $(executable)

$(builddir):
	mkdir $(builddir)

$(executable): $(objects) $(library) $(java_classes) $(fs_classes)
	$(CC) $(CFLAGS) $(INCLUDES) $(LDFLAGS) src/javafuse.c -o $@

$(library): $(objects)
	$(CC) -shared $(objects) -o $(builddir)/$@

$(builddir)/%.o: %.c
	$(CC) -c -fPIC $(CFLAGS) $(INCLUDES) $< -o $@

$(builddir)/javafuse/%.class: %.java
	$(JAVAC) $(JFLAGS) -cp $(CLASSPATH) $^ -d $(builddir)

clean:
	rm -rf $(builddir)/* $(executable)

#include $(deps)

#$(builddir)/%.dep: %.c
#	@set -e; rm -f $@; \
#		gcc -MM $(CFLAGS) $(INCLUDES) $< > $@.$$$$; \
#		sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
#		rm -f $@.$$$$
