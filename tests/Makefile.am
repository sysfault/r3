# INCLUDES                    = @CHECK_CFLAGS@
# if HAVE_CHECK
# TESTS                       = check_tree
# else
# TESTS                       =
# endif
TESTS                       = check_tree

if ENABLE_GRAPHVIZ
TESTS += check_gvc
check_gvc_SOURCES = check_gvc.c bench.c
check_gvc_LDADD=$(DEPS_LIBS) -L$(top_builddir)/src -lr3 @CHECK_LIBS@
check_gvc_CFLAGS=$(DEPS_CFLAGS) -I$(top_builddir) -I$(top_builddir)/include @CHECK_CFLAGS@
endif


# noinst_PROGRAMS             = $(TESTS)
check_tree_SOURCES = check_tree.c bench.c
check_tree_LDADD=$(DEPS_LIBS) -L$(top_builddir)/src -lr3 @CHECK_LIBS@
check_tree_CFLAGS=$(DEPS_CFLAGS) -I$(top_builddir) -I$(top_builddir)/include @CHECK_CFLAGS@
check_PROGRAMS = $(TESTS)


# AM_CFLAGS=$(DEPS_CFLAGS) -I$(top_builddir)/include
# AM_CFLAGS=$(DEPS_CFLAGS) -I$(top_builddir) -I$(top_builddir)/include
CLEANFILES                  = check_tree.log
