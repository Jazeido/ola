# here we define common flags for C++ targets
WARNING_CXXFLAGS = -I$(top_srcdir)/include \
                   -I$(top_builddir)/include \
                   -I$(top_srcdir) \
                   -I$(top_builddir) \
                   -Wall -Wformat -W -fvisibility-inlines-hidden \
                   $(libprotobuf_CFLAGS)

COMMON_CXXFLAGS = $(WARNING_CXXFLAGS)

# the genererated protobuf files don't compile with -Werror on win32
if ! USING_WIN32
if FATAL_WARNINGS
  COMMON_CXXFLAGS += -Werror
endif
endif

# AM_CXXFLAGS is used when target_CXXFLAGS isn't defined
AM_CXXFLAGS = $(COMMON_CXXFLAGS)

COMMON_TESTING_LIBS = $(CPPUNIT_LIBS) \
                      $(top_builddir)/common/testing/libolatesting.la \
                      $(top_builddir)/common/testing/libtestmain.la
# Due to MinGW's handling of library archives, we need to append this
if USING_WIN32
COMMON_TESTING_LIBS += $(CPPUNIT_LIBS)
endif

COMMON_TESTING_FLAGS = $(COMMON_CXXFLAGS) $(CPPUNIT_CFLAGS) \
                       -DTEST_SRC_DIR=\"$(srcdir)\"
