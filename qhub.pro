TEMPLATE = subdirs

src_lib.subdir = qhub_src
src_lib.target = lib

src_example.subdir  = qhub_example
src_example.target  = example
src_example.depends = lib

SUBDIRS = qhub_src qhub_example
