Index
------------------------------------------------------------
I.   About ZEngine
II.  Getting ZEngine
III. Building ZEngine
IV.  Using ZEngine
V.   Legal Overview
VI.  History of ZEngine
------------------------------------------------------------
I. About ZEngine 0.8

ZEngine is a game library which is designed for any platform that SDL and/or
OpenGL is available on.  ZEngine is a set of classes and a main ZEngine class 
which are designed to make game development easier and more organized.  As of 
0.7.7 ZEngine can use OpenGL to do the 2D display, so it is much faster and can
take advantage of hardware accelerated features.   This file provides a simple
overview of using it, more on the subject can be found in the docs and at
http://zengine.sourceforge.net/tutorials/.
------------------------------------------------------------
II. Getting ZEngine:

Support comes from: http://conceptofzero.net/
The sourceforge page: http://zengine.sourceforge.net/
The project page: http://sourceforge.net/projects/zengine/
The CVS page: http://sourceforge.net/cvs/?group_id=62098
------------------------------------------------------------
III. Building ZEngine:

ZEngine can be built on any system any system that has SDL and OpenGL 
available. If you are in VC++ the folder vc7 contains project files for use,
Dev-C++ project files are in the devcpp folder, and if you are in a gcc 
compiler you can change the config & makefile to meet your needs.
-If you are using an IDE you will need to add the path to the dependencies (SDL
and others) as well as the path to ZEngine before building.

See dependencies.txt for information on obtaining the dependencies.

If you are having a problem building ask at the ZEngine forum.
(Click forum link at http://zengine.sourceforge.net)
------------------------------------------------------------
IV. Using ZEngine:

Using ZEngine is as easy as having a look at the sample programs and nice
documentation provided and setting the compiler to link with the ZEngine lib
and include the ZEngine include files.  ZEngine allows you to decide what 
external libraries (other than SDL and OpenGL which are required) you want
to use when you build the library file.  Depending on which libraries you are
using you will need to distribute various files with your program, but none
are part of ZEngine, but instead are files in use by the dependencies.
------------------------------------------------------------
V. Legal Overview:

The world of open source licenses can be confusing, if you are not familiar 
with the LGPL I recommend reading it, as most libraries ZEngine makes use of
are licensed under it. (LGPL.txt is included) ZEngine itself has no real 
restrictions on use, and is under the OSI-certified BSD license 
(see licensing.txt). Below is a quick guide to how you would distribute 
a package making use of ZEngine.

Closed-Source Application using ZEngine:
    (see licensing-template.txt)
    -Include required DLLs or dynamic modules
    -Include notice of which libraries you used, and have a place for user to
    dowload them from your website.
    -If you are using non-LGPL libraries there may be other requirements.

(licensing-template.txt is included to help you comply with the LGPL)

See dependencies.txt for information on source to the dependencies.

Adding to ZEngine:
    -This can currently be done with no restrictions, but I do ask that 
    you submit your changes back to the community if possible.
------------------------------------------------------------
History of ZEngine:
    The changelog may not show it but 0.1 to 0.6 were some of the biggest 
changes, often I'd rewrite massive portions of code, I wasn't keeping the 
changelog, and I wasn't testing for compatibility. ZEngine was still 
designed to be an engine that only CoZ members used, hardly clean but useful
enough to speed up the process of making games, even if it was going to be 
open source, I figured I'd put it out there as example code, but never really
 make it an open source project.
    By 0.5 and 0.6 I really got the idea that this could become something that
some other people may want to use, so I started to document everything and I 
began to prepare for the Linux version.  During 0.6.x I was struggling with 
organizing the code as well as licensing, and SDL 1.2.5 was released which
turned into an unnecessary rewrite.  (Honestly nothing changed in SDL that 
affected ZEngine, but for some reason I felt ZEngine would be much better if 
the code was cleaner and I tried to reduce the amount of legacy code left from
the early versions.)
    0.6.3 made the jump to 0.7.0 because there really was a change in ZEngine, 
the target audience as well as the code base.  With ZConfigFile, ZEngine 
started to gain features that SDL didn't have, so it wasn't just a SDL wrapper
anymore. 0.7.x turned into a series of major releases, with some major changes
including 0.7.3, 0.7.4, and the major 0.7.7, which almost became 0.8.0.
    0.8.0 is a whole new ZEngine, I estimate that no more than 2% of the 
original code remains, almost everything I added in 0.3.0 is still there, but
other than that, nothing stuck until 0.7 for example the ZEngine class itself
has gone 2 complete rewrites since 0.1.  I used to work in DirectX a lot, and
ZEngine addresses a lot of grieviances I had with DirectX, ZEngine code is a 
lot shorter, and is a good deal easier to read, everything is integrated, 
unlike DirectX where Input and Graphics were entirely separate things. ZEngine
runs a lot faster on most systems now, due to the OpenGL rendering, and as a
little treat I threw in just in time for the 0.8.0 release, ZEngine attempts 
to detect surface loss, and even provides methods to restore it.
    From 0.8.0 to 0.8.5 some very large changes were made to separate ZEngine
from other simple 2D apis.  Features such as an optional framerate limiter,
error handling, convenient overloads, an extremely extensible particle system,
and better support for more compilers.  Also as ZEngine stabilizes more small
features, bugfixes, cleanups and enhancements to existing code have been made
and the number of users (at least what is indicated by the number of emails
and IMs I've been getting) has been rising steadily.

    -James Turk james@conceptofzero.net
