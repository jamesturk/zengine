About ZEngine 0.7.x

ZEngine is a game library which is designed to compile that SDL and OpenGL
are available on.  ZEngine is a set of classes and a main ZEngine class which
are designed to make game development easier and more organized.  As of 0.7.7
ZEngine uses OpenGL to do the 2D display, so it is much faster and can take
advantage of hardware accelerated features. 

Getting ZEngine:

The real home is at: http://conceptofzero.net/
The sourceforge page: http://zengine.sourceforge.net/
The project page: http://sourceforge.net/projects/zengine/
The CVS page: http://sourceforge.net/cvs/?group_id=62098

Building ZEngine:

ZEngine can be built on any system that has SDL and OpenGL available.  It is
currently being developed on Redhat 8.0 and Windows 2000/XP.  If you are on
windows the folder vc7 contains project files for use, and if you are using
mingw or cygwin you can replace the linux makefile with makefile.mingw32.
-If you are using VC++ you will need to add the path to the dependencies (SDL 
and others) as well as the path to ZEngine before building.
-If you are using gcc on any system you will need to modify the makefile you
are using to set the proper include and lib paths.
If you are having a problem building ask on http://conceptofzero.net/forums.

Using ZEngine:

Using ZEngine is as easy as having a look at the sample programs and nice
documentation provided and setting the compiler to link with the ZEngine lib
and include the ZEngine include files.  ZEngine allows you to decide what 
external libraries (other than SDL and OpenGL which are required) you want
to use when you build the library file.  Depending on which libraries you are
using you will need to distribute various files with your program, but none
are part of ZEngine, but instead are files in use by the dependencies.

Legal Overview:

The world of open source licenses can be confusing, if you are not familiar 
with the LGPL I recommend reading it, as most libraries ZEngine makes use of
are licensed under it.  ZEngine itself has no real restrictions on use, and is
under the OSI-certified BSD license (see licensing.txt). Below are quick
guides of how you would distribute various packages making use of ZEngine.

Closed-Source Application using ZEngine:
    -Include required DLLs or .so dynamic modules
    -Include notice of which libraries you used, and have a place for them to
    dowload them from your website.
    -If you are using non-LGPL libraries there may be other requirements.
    (Open-Source applications do not need to have a link to a download for
    LGPL-licensed libraries.)
    
Adding to ZEngine:
    -This can currently be done with no restrictions, but we do ask that 
    you submit your changes back to the community.

-James Turk james@conceptofzero.net

