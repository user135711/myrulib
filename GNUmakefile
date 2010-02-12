# =========================================================================
#     This makefile was generated by
#     Bakefile 0.2.8 (http://www.bakefile.org)
#     Do not modify, all changes will be overwritten!
# =========================================================================



# -------------------------------------------------------------------------
# These are configurable options:
# -------------------------------------------------------------------------

# 'install' program location 
INSTALL ?= install

# Destination root (/ is used if empty) 
DESTDIR ?= 

#  
AR ?= ar

#  
RANLIB ?= ranlib

# C compiler 
CC = gcc

# C++ compiler 
CXX = `$(WX_CONFIG) --cxx`

# Standard flags for CC 
CFLAGS ?= 

# Standard flags for C++ 
CXXFLAGS ?= 

# Standard preprocessor flags (common for CC and CXX) 
CPPFLAGS ?= 

# Standard linker flags 
LDFLAGS ?= 

# Location and arguments of wx-config script 
WX_CONFIG ?= wx-config

# Port of the wx library to build against [gtk1,gtk2,msw,x11,motif,mgl,mac,dfb]
WX_PORT ?= gtk2

# Use DLL build of wx library to use? [0,1]
WX_SHARED ?= 1

# Compile Unicode build of wxWidgets? [0,1]
WX_UNICODE ?= 1

# Use debug build of wxWidgets (define __WXDEBUG__)? [0,1]
WX_DEBUG ?= 0

# Version of the wx library to build against. 
WX_VERSION ?= 2.8



# -------------------------------------------------------------------------
# Do not modify the rest of this file!
# -------------------------------------------------------------------------

### Variables: ###

CPPDEPS = -MT$@ -MF`echo $@ | sed -e 's,\.o$$,.d,'` -MD -MP
WX_VERSION_MAJOR = $(shell echo $(WX_VERSION) | cut -c1,1)
WX_VERSION_MINOR = $(shell echo $(WX_VERSION) | cut -c2,2)
WX_CONFIG_FLAGS = $(WX_CONFIG_DEBUG_FLAG) $(WX_CONFIG_UNICODE_FLAG) \
	$(WX_CONFIG_SHARED_FLAG) --toolkit=$(WX_PORT) \
	--version=$(WX_VERSION_MAJOR).$(WX_VERSION_MINOR)
WXSQLITE3_STATIC_CXXFLAGS = -IWxSQLite3 -IWxSQLite3 `$(WX_CONFIG) --cxxflags \
	$(WX_CONFIG_FLAGS)` $(CPPFLAGS) $(CXXFLAGS)
WXSQLITE3_STATIC_OBJECTS =  \
	build/wxsqlite3_static_wxsqlite3.o
MYRULIB_CFLAGS = -IWxSQLite3 -O2 `$(WX_CONFIG) --cflags $(WX_CONFIG_FLAGS)` \
	$(CPPFLAGS) $(CFLAGS)
MYRULIB_CXXFLAGS = -IWxSQLite3 -O2 `$(WX_CONFIG) --cxxflags $(WX_CONFIG_FLAGS)` \
	$(CPPFLAGS) $(CXXFLAGS)
MYRULIB_OBJECTS =  \
	build/myrulib_BaseThread.o \
	build/myrulib_ExpThread.o \
	build/myrulib_ExternalDlg.o \
	build/myrulib_FbAboutDlg.o \
	build/myrulib_FbAuthorDlg.o \
	build/myrulib_FbAuthorThread.o \
	build/myrulib_FbBookData.o \
	build/myrulib_FbBookEvent.o \
	build/myrulib_FbBookList.o \
	build/myrulib_FbBookMenu.o \
	build/myrulib_FbBookPanel.o \
	build/myrulib_FbBookThread.o \
	build/myrulib_FbCheckList.o \
	build/myrulib_FbColumnDlg.o \
	build/myrulib_FbConfigDlg.o \
	build/myrulib_FbConst.o \
	build/myrulib_FbDatabase.o \
	build/myrulib_FbDataOpenDlg.o \
	build/myrulib_FbDataPath.o \
	build/myrulib_FbEditBook.o \
	build/myrulib_FbExtractInfo.o \
	build/myrulib_FbDownloader.o \
	build/myrulib_FbFilterDlg.o \
	build/myrulib_FbFilterObj.o \
	build/myrulib_FbFrameAuthor.o \
	build/myrulib_FbFrameBase.o \
	build/myrulib_FbFrameDownld.o \
	build/myrulib_FbFrameFolder.o \
	build/myrulib_FbFrameInfo.o \
	build/myrulib_FbFrameHtml.o \
	build/myrulib_FbFrameGenres.o \
	build/myrulib_FbFrameSearch.o \
	build/myrulib_FbFrameSequen.o \
	build/myrulib_FbGenres.o \
	build/myrulib_FbHtmlWindow.o \
	build/myrulib_FbImportThread.o \
	build/myrulib_FbLogStream.o \
	build/myrulib_FbMainFrame.o \
	build/myrulib_FbMainMenu.o \
	build/myrulib_FbMasterData.o \
	build/myrulib_FbMasterList.o \
	build/myrulib_FbMenu.o \
	build/myrulib_FbNotebook.o \
	build/myrulib_FbParams.o \
	build/myrulib_FbReplaceDlg.o \
	build/myrulib_FbTreeListCtrl.o \
	build/myrulib_FbUpdateThread.o \
	build/myrulib_FbViewerDlg.o \
	build/myrulib_FbWindow.o \
	build/myrulib_ImpContext.o \
	build/myrulib_InfoCash.o \
	build/myrulib_InfoThread.o \
	build/myrulib_LimitedTextCtrl.o \
	build/myrulib_MyRuLibApp.o \
	build/myrulib_ParseCtx.o \
	build/myrulib_ProgressBar.o \
	build/myrulib_SettingsDlg.o \
	build/myrulib_TitleThread.o \
	build/myrulib_ZipReader.o \
	build/myrulib_md5.o \
	build/myrulib_base64.o \
	build/myrulib_treelistctrl.o

### Conditionally set variables: ###

ifeq ($(WX_DEBUG),0)
WX_CONFIG_DEBUG_FLAG = --debug=no
endif
ifeq ($(WX_DEBUG),1)
WX_CONFIG_DEBUG_FLAG = --debug=yes
endif
ifeq ($(WX_UNICODE),0)
WX_CONFIG_UNICODE_FLAG = --unicode=no
endif
ifeq ($(WX_UNICODE),1)
WX_CONFIG_UNICODE_FLAG = --unicode=yes
endif
ifeq ($(WX_SHARED),0)
WX_CONFIG_SHARED_FLAG = --static=yes
endif
ifeq ($(WX_SHARED),1)
WX_CONFIG_SHARED_FLAG = --static=no
endif


all: build
build:
	@mkdir -p build

### Targets: ###

all: test_for_selected_wxbuild build/libwxsqlite3_static.a build/myrulib

install: install_myrulib
	$(INSTALL) -d $(DESTDIR)/usr/share/icons/hicolor/48x48/apps
	(cd MyRuLib/desktop ; $(INSTALL) -m 644  myrulib.png $(DESTDIR)/usr/share/icons/hicolor/48x48/apps)
	$(INSTALL) -d $(DESTDIR)/usr/share/applications
	(cd MyRuLib/desktop ; $(INSTALL) -m 644  myrulib.desktop $(DESTDIR)/usr/share/applications)
	ln -s ../icons/hicolor/48x48/apps/myrulib.png /usr/share/pixmaps/myrulib.png

uninstall: uninstall_myrulib
	(cd $(DESTDIR)/usr/share/icons/hicolor/48x48/apps ; rm -f myrulib.png)
	(cd $(DESTDIR)/usr/share/applications ; rm -f myrulib.desktop)
	rm -f /usr/share/pixmaps/myrulib.png

clean: 
	rm -f build/*.o
	rm -f build/*.d
	rm -f build/libwxsqlite3_static.a
	rm -f build/myrulib

test_for_selected_wxbuild: 
	@$(WX_CONFIG) $(WX_CONFIG_FLAGS)

build/libwxsqlite3_static.a: $(WXSQLITE3_STATIC_OBJECTS)
	rm -f $@
	$(AR) rcu $@ $(WXSQLITE3_STATIC_OBJECTS)
	$(RANLIB) $@

build/myrulib: $(MYRULIB_OBJECTS) build/libwxsqlite3_static.a
	$(CXX) -o $@ $(MYRULIB_OBJECTS)     $(LDFLAGS)  build/libwxsqlite3_static.a -lexpat -lsqlite3 `$(WX_CONFIG) $(WX_CONFIG_FLAGS) --libs aui,html,core,net,base`
	strip ./build/myrulib
	rm -f ./build/myrulib.png

install_myrulib: build/myrulib
	$(INSTALL) -d $(DESTDIR)/usr/bin
	install -c build/myrulib $(DESTDIR)/usr/bin

uninstall_myrulib: 
	rm -f $(DESTDIR)/usr/bin/myrulib

build/wxsqlite3_static_wxsqlite3.o: ./WxSQLite3/wxsqlite3.cpp
	$(CXX) -c -o $@ $(WXSQLITE3_STATIC_CXXFLAGS) $(CPPDEPS) $<

build/myrulib_BaseThread.o: ./MyRuLib/BaseThread.cpp
	$(CXX) -c -o $@ $(MYRULIB_CXXFLAGS) $(CPPDEPS) $<

build/myrulib_ExpThread.o: ./MyRuLib/ExpThread.cpp
	$(CXX) -c -o $@ $(MYRULIB_CXXFLAGS) $(CPPDEPS) $<

build/myrulib_ExternalDlg.o: ./MyRuLib/ExternalDlg.cpp
	$(CXX) -c -o $@ $(MYRULIB_CXXFLAGS) $(CPPDEPS) $<

build/myrulib_FbAboutDlg.o: ./MyRuLib/FbAboutDlg.cpp
	$(CXX) -c -o $@ $(MYRULIB_CXXFLAGS) $(CPPDEPS) $<

build/myrulib_FbAuthorDlg.o: ./MyRuLib/FbAuthorDlg.cpp
	$(CXX) -c -o $@ $(MYRULIB_CXXFLAGS) $(CPPDEPS) $<

build/myrulib_FbAuthorThread.o: ./MyRuLib/FbAuthorThread.cpp
	$(CXX) -c -o $@ $(MYRULIB_CXXFLAGS) $(CPPDEPS) $<

build/myrulib_FbBookData.o: ./MyRuLib/FbBookData.cpp
	$(CXX) -c -o $@ $(MYRULIB_CXXFLAGS) $(CPPDEPS) $<

build/myrulib_FbBookEvent.o: ./MyRuLib/FbBookEvent.cpp
	$(CXX) -c -o $@ $(MYRULIB_CXXFLAGS) $(CPPDEPS) $<

build/myrulib_FbBookList.o: ./MyRuLib/FbBookList.cpp
	$(CXX) -c -o $@ $(MYRULIB_CXXFLAGS) $(CPPDEPS) $<

build/myrulib_FbBookMenu.o: ./MyRuLib/FbBookMenu.cpp
	$(CXX) -c -o $@ $(MYRULIB_CXXFLAGS) $(CPPDEPS) $<

build/myrulib_FbBookPanel.o: ./MyRuLib/FbBookPanel.cpp
	$(CXX) -c -o $@ $(MYRULIB_CXXFLAGS) $(CPPDEPS) $<

build/myrulib_FbBookThread.o: ./MyRuLib/FbBookThread.cpp
	$(CXX) -c -o $@ $(MYRULIB_CXXFLAGS) $(CPPDEPS) $<

build/myrulib_FbCheckList.o: ./MyRuLib/FbCheckList.cpp
	$(CXX) -c -o $@ $(MYRULIB_CXXFLAGS) $(CPPDEPS) $<

build/myrulib_FbColumnDlg.o: ./MyRuLib/FbColumnDlg.cpp
	$(CXX) -c -o $@ $(MYRULIB_CXXFLAGS) $(CPPDEPS) $<

build/myrulib_FbConfigDlg.o: ./MyRuLib/FbConfigDlg.cpp
	$(CXX) -c -o $@ $(MYRULIB_CXXFLAGS) $(CPPDEPS) $<

build/myrulib_FbConst.o: ./MyRuLib/FbConst.cpp
	$(CXX) -c -o $@ $(MYRULIB_CXXFLAGS) $(CPPDEPS) $<

build/myrulib_FbDatabase.o: ./MyRuLib/FbDatabase.cpp
	$(CXX) -c -o $@ $(MYRULIB_CXXFLAGS) $(CPPDEPS) $<

build/myrulib_FbDataOpenDlg.o: ./MyRuLib/FbDataOpenDlg.cpp
	$(CXX) -c -o $@ $(MYRULIB_CXXFLAGS) $(CPPDEPS) $<

build/myrulib_FbDataPath.o: ./MyRuLib/FbDataPath.cpp
	$(CXX) -c -o $@ $(MYRULIB_CXXFLAGS) $(CPPDEPS) $<

build/myrulib_FbEditBook.o: ./MyRuLib/FbEditBook.cpp
	$(CXX) -c -o $@ $(MYRULIB_CXXFLAGS) $(CPPDEPS) $<

build/myrulib_FbExtractInfo.o: ./MyRuLib/FbExtractInfo.cpp
	$(CXX) -c -o $@ $(MYRULIB_CXXFLAGS) $(CPPDEPS) $<

build/myrulib_FbDownloader.o: ./MyRuLib/FbDownloader.cpp
	$(CXX) -c -o $@ $(MYRULIB_CXXFLAGS) $(CPPDEPS) $<

build/myrulib_FbFilterDlg.o: ./MyRuLib/FbFilterDlg.cpp
	$(CXX) -c -o $@ $(MYRULIB_CXXFLAGS) $(CPPDEPS) $<

build/myrulib_FbFilterObj.o: ./MyRuLib/FbFilterObj.cpp
	$(CXX) -c -o $@ $(MYRULIB_CXXFLAGS) $(CPPDEPS) $<

build/myrulib_FbFrameAuthor.o: ./MyRuLib/FbFrameAuthor.cpp
	$(CXX) -c -o $@ $(MYRULIB_CXXFLAGS) $(CPPDEPS) $<

build/myrulib_FbFrameBase.o: ./MyRuLib/FbFrameBase.cpp
	$(CXX) -c -o $@ $(MYRULIB_CXXFLAGS) $(CPPDEPS) $<

build/myrulib_FbFrameDownld.o: ./MyRuLib/FbFrameDownld.cpp
	$(CXX) -c -o $@ $(MYRULIB_CXXFLAGS) $(CPPDEPS) $<

build/myrulib_FbFrameFolder.o: ./MyRuLib/FbFrameFolder.cpp
	$(CXX) -c -o $@ $(MYRULIB_CXXFLAGS) $(CPPDEPS) $<

build/myrulib_FbFrameInfo.o: ./MyRuLib/FbFrameInfo.cpp
	$(CXX) -c -o $@ $(MYRULIB_CXXFLAGS) $(CPPDEPS) $<

build/myrulib_FbFrameHtml.o: ./MyRuLib/FbFrameHtml.cpp
	$(CXX) -c -o $@ $(MYRULIB_CXXFLAGS) $(CPPDEPS) $<

build/myrulib_FbFrameGenres.o: ./MyRuLib/FbFrameGenres.cpp
	$(CXX) -c -o $@ $(MYRULIB_CXXFLAGS) $(CPPDEPS) $<

build/myrulib_FbFrameSearch.o: ./MyRuLib/FbFrameSearch.cpp
	$(CXX) -c -o $@ $(MYRULIB_CXXFLAGS) $(CPPDEPS) $<

build/myrulib_FbFrameSequen.o: ./MyRuLib/FbFrameSequen.cpp
	$(CXX) -c -o $@ $(MYRULIB_CXXFLAGS) $(CPPDEPS) $<

build/myrulib_FbGenres.o: ./MyRuLib/FbGenres.cpp
	$(CXX) -c -o $@ $(MYRULIB_CXXFLAGS) $(CPPDEPS) $<

build/myrulib_FbHtmlWindow.o: ./MyRuLib/FbHtmlWindow.cpp
	$(CXX) -c -o $@ $(MYRULIB_CXXFLAGS) $(CPPDEPS) $<

build/myrulib_FbImportThread.o: ./MyRuLib/FbImportThread.cpp
	$(CXX) -c -o $@ $(MYRULIB_CXXFLAGS) $(CPPDEPS) $<

build/myrulib_FbLogStream.o: ./MyRuLib/FbLogStream.cpp
	$(CXX) -c -o $@ $(MYRULIB_CXXFLAGS) $(CPPDEPS) $<

build/myrulib_FbMainFrame.o: ./MyRuLib/FbMainFrame.cpp
	$(CXX) -c -o $@ $(MYRULIB_CXXFLAGS) $(CPPDEPS) $<

build/myrulib_FbMainMenu.o: ./MyRuLib/FbMainMenu.cpp
	$(CXX) -c -o $@ $(MYRULIB_CXXFLAGS) $(CPPDEPS) $<

build/myrulib_FbMasterData.o: ./MyRuLib/FbMasterData.cpp
	$(CXX) -c -o $@ $(MYRULIB_CXXFLAGS) $(CPPDEPS) $<

build/myrulib_FbMasterList.o: ./MyRuLib/FbMasterList.cpp
	$(CXX) -c -o $@ $(MYRULIB_CXXFLAGS) $(CPPDEPS) $<

build/myrulib_FbMenu.o: ./MyRuLib/FbMenu.cpp
	$(CXX) -c -o $@ $(MYRULIB_CXXFLAGS) $(CPPDEPS) $<

build/myrulib_FbNotebook.o: ./MyRuLib/FbNotebook.cpp
	$(CXX) -c -o $@ $(MYRULIB_CXXFLAGS) $(CPPDEPS) $<

build/myrulib_FbParams.o: ./MyRuLib/FbParams.cpp
	$(CXX) -c -o $@ $(MYRULIB_CXXFLAGS) $(CPPDEPS) $<

build/myrulib_FbReplaceDlg.o: ./MyRuLib/FbReplaceDlg.cpp
	$(CXX) -c -o $@ $(MYRULIB_CXXFLAGS) $(CPPDEPS) $<

build/myrulib_FbTreeListCtrl.o: ./MyRuLib/FbTreeListCtrl.cpp
	$(CXX) -c -o $@ $(MYRULIB_CXXFLAGS) $(CPPDEPS) $<

build/myrulib_FbUpdateThread.o: ./MyRuLib/FbUpdateThread.cpp
	$(CXX) -c -o $@ $(MYRULIB_CXXFLAGS) $(CPPDEPS) $<

build/myrulib_FbViewerDlg.o: ./MyRuLib/FbViewerDlg.cpp
	$(CXX) -c -o $@ $(MYRULIB_CXXFLAGS) $(CPPDEPS) $<

build/myrulib_FbWindow.o: ./MyRuLib/FbWindow.cpp
	$(CXX) -c -o $@ $(MYRULIB_CXXFLAGS) $(CPPDEPS) $<

build/myrulib_ImpContext.o: ./MyRuLib/ImpContext.cpp
	$(CXX) -c -o $@ $(MYRULIB_CXXFLAGS) $(CPPDEPS) $<

build/myrulib_InfoCash.o: ./MyRuLib/InfoCash.cpp
	$(CXX) -c -o $@ $(MYRULIB_CXXFLAGS) $(CPPDEPS) $<

build/myrulib_InfoThread.o: ./MyRuLib/InfoThread.cpp
	$(CXX) -c -o $@ $(MYRULIB_CXXFLAGS) $(CPPDEPS) $<

build/myrulib_LimitedTextCtrl.o: ./MyRuLib/LimitedTextCtrl.cpp
	$(CXX) -c -o $@ $(MYRULIB_CXXFLAGS) $(CPPDEPS) $<

build/myrulib_MyRuLibApp.o: ./MyRuLib/MyRuLibApp.cpp
	$(CXX) -c -o $@ $(MYRULIB_CXXFLAGS) $(CPPDEPS) $<

build/myrulib_ParseCtx.o: ./MyRuLib/ParseCtx.cpp
	$(CXX) -c -o $@ $(MYRULIB_CXXFLAGS) $(CPPDEPS) $<

build/myrulib_ProgressBar.o: ./MyRuLib/ProgressBar.cpp
	$(CXX) -c -o $@ $(MYRULIB_CXXFLAGS) $(CPPDEPS) $<

build/myrulib_SettingsDlg.o: ./MyRuLib/SettingsDlg.cpp
	$(CXX) -c -o $@ $(MYRULIB_CXXFLAGS) $(CPPDEPS) $<

build/myrulib_TitleThread.o: ./MyRuLib/TitleThread.cpp
	$(CXX) -c -o $@ $(MYRULIB_CXXFLAGS) $(CPPDEPS) $<

build/myrulib_ZipReader.o: ./MyRuLib/ZipReader.cpp
	$(CXX) -c -o $@ $(MYRULIB_CXXFLAGS) $(CPPDEPS) $<

build/myrulib_md5.o: ./MyRuLib/md5.c
	$(CC) -c -o $@ $(MYRULIB_CFLAGS) $(CPPDEPS) $<

build/myrulib_base64.o: ./MyRuLib/wx/base64.cpp
	$(CXX) -c -o $@ $(MYRULIB_CXXFLAGS) $(CPPDEPS) $<

build/myrulib_treelistctrl.o: ./MyRuLib/wx/treelistctrl.cpp
	$(CXX) -c -o $@ $(MYRULIB_CXXFLAGS) $(CPPDEPS) $<

.PHONY: all install uninstall clean install_myrulib uninstall_myrulib


# Dependencies tracking:
-include build/*.d
