# Mounts the NullFS file system, which is part of the nullfs package, on a 
# folder called tmp/

# The -f flag and the big_writes and auto_cache options are FUSE parameters.

. ./build.conf

LD_LIBRARY_PATH=build:$JDK_HOME/jre/lib/i386/server ./javafuse -f -o big_writes -o auto_cache -Cnullfs/NullFS -Ffs/nullfs/nullfs.config tmp/
