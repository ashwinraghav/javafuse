# To build user filesystems. Add your build rules here as needed!

include ../build.conf

builddir = build

CC = gcc
JAVAC = javac
JAVA = java
JFLAGS = -Xlint -source 5
CFLAGS = -c -g -Wall `pkg-config --cflags fuse`
LDFLAGS = `pkg-config --libs fuse` $(shell java -jar ../util/DumpJVMLdPath.jar) -ljvm
INCLUDES = -I$(includedir) -I$(JDK_HOME)/include -I$(JDK_HOME)/include/linux
CLASSPATH = ../build:$(builddir)

nullfsdir = nullfs
nullfs_sources = $(shell find $(nullfsdir) -type f -name '*.java')

all: $(builddir) NullFS

$(builddir):
	mkdir $(builddir)

NullFS: $(nullfs_sources)
	$(JAVAC) $(JFLAGS) -cp $(CLASSPATH) $^ -d $(builddir)

clean:
	rm -rf $(builddir)/$(spadedir)
