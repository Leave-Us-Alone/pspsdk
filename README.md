Ver 0.11.2r3. Took from [sourceforge.](https://sourceforge.net/projects/minpspw/files/SDK/)
```
Welcome to the MINPSPW (Minimalist PSP homebrew SDK for Windows).

With this SDK you are able to code your own applications for the amazing
device that is the Sony PlayStation Portable. If you finished the installation
and you are reading this document you are ready to code.

Pick the code examples from the psp/sdk/samples directory and investigate
the code. To write your own applications, just grab your favourite IDE for
C/C++ and start right away, use the makefile templates from the samples
directory and remember that the compiler is based on GNU GCC compiler set
so no Microsoft extensions are available for you.


===============================================================================
 If you got this as a collection of shell scripts
===============================================================================

This program will automatically build and install a compiler and other
tools used in the creation of homebrew software for the Sony Playstation
Portable handheld videogame system.


===============================================================================
 TODO
===============================================================================
0.11 Still to decide....
* Added MacOSX support
* Reverted Binutils to 2.16.1 since there is a bug with 2.18 that causes
  bad code for example on Daedalus Project.

===============================================================================
 Changelog
===============================================================================
0.10.1
* fixed pspmath.h file for C++
* Added D support to GDB
* Fix pspsh for windows to run within eclipse
* Lib updates:
  - zlib updated to 1.2.5
  - bzip2 updated to 1.0.6
  - freetype updated to 2.4.3
  - jpeg updated to 8b
  - bulletml updated to 0.0.6
  - libmad updated to 0.15.1b
  - libmikmod updated to 3.1.11
  - libogg updated to 1.2.1
  - libpng updated to 1.4.4
  - libvorbis updated to 1.3.2
  - lua updated to 5.1.4
  - SDL updated to 1.2.14
  - SDL_gfx updated to 2.0.22
  - SDL_image updated to 1.2.10
  - SDL_mixer updated to 1.2.11
  - SDL_ttf updated to 2.0.10
  - cal3d updated to 0.11.0
  - tinyxml updated to 2.6.1
* Initial support for linux 64bit
* Initial support for building under MacOSX
* Fix pspsh under linux (readline was disabled by mistake)


0.10.0
* new devpaks
  - allegro 4.4.1.1
  - OSLib replaced with OSLib_MOD
  - Bullet Physics
  - CubicVR game engine
* Added D programming language D 1.060 as a supported language (experimental)
  - Added a sample Hello World to the SDK

0.9.6
* pspsh does not depend on cygwin and is native
* remotejoy SDL is also included as a native binary (no cygwin)
* win32 dependencies updated
 - zlib 1.2.5
 - SDL 1.2.14
 - readline 5.1 (same as gdb)
 - libiconv 1.13.1
 - pthreads 2.8.0
* updated the fpulib trig functions can use the FPU processor but
  we either use vfpu or software impl using libm. This can help to
  make a bit faster code if we do not need vectors.
* Updated newlib to 1.18
 - wide-char enhancements
 - long double math routines added for platforms where LDBL == DBL
 - long long math routines added
 - math cleanup
 - major locale charset overhaul including added charsets
 - various cleanups
 - various bug fixes
* Updated the dev environment to build under Windows Vista
* Updated binutils to 2.18 (for better integration with gcc 4.3.x)
* removed the patch that defines long as 64bit back to 32bit. This can
  lead to faster code but breaks old compiled libraries
* Disabled CDT-5.0.x bug fix
* gcov builds properly but not fully tested if works as expected
* added fixes from Luqman Aden in TinyXML
* added libmpeg2 devpak
* added bullet physics devpak
* windows tools are linked against pthreads, if thereads are used it can
  improved performance on the development side.

0.9.5
* Start to port the project also for OpenSolaris 2009.06 (vanilla).
* Added Visual Studio Project Files from Lukas Przytula
* 38 Devpaks as default instead of the base 20

0.9.4
* Start to port the project also for Ubuntu (vanilla).

0.9.3
* Patch the GCC for Windows On Eclipse CDT 5.0.2 bug (to be removed in the next
  major release).

0.9.2
* Newlib 1.17.0
  * new C99 wide-char function additions
  * movement of regex functions from sys/linux directory into
    shared libc/posix directory
  * string function optimizations
  * redesign of formatted I/O to reduce dependencies when using
    sprintf/sscanf family of functions
  * numerous warning cleanups
  * various bug fixes
* Patched SDK for missing functions (only declared on the ASM side)
* GDB works with the Slim (wasn't reading the correct memory address if the
  variables where above 0x0A000000
* Added threading support to GCC, which will improve Objective-C and enable
  exception handling on C++

0.8.11
* GMP updated to 4.2.4
* GCC updated to 4.3.3
* SDK updated to latest SVN

0.8.10
* Update to Newlib 1.16
* Pack the libraries into the Installer
  - zlib
  - bzip2
  - freetype
  - jpeg
  - libbulletml
  - libmad
  - libmikmod
  - libogg
  - libpng
  - libpspvram
  - libTremor
  - libvorbis
  - lua
  - pspgl
  - pspirkeyb
  - sqlite
  - SDL
  - SDL_gfx
  - SDL_image
  - SDL_mixer
  - SDL_ttf
  - smpeg
  - zziplib
 * Fix the Objective-C sample since it didn't show anything.

0.8.9
* Added Objective-C++ support to the toochain.
* Updated SDK docs to build without errors
* dot fixed now images in the docs are readable
* Shrunk the installer

0.8.8
* Added Objective-C support to the toochain. And a sample.

0.8.7
* Updated SVN
* Since ps2dev started to use the patches I was hosting, legacy builds are over
* Update GCC 4.3.2
* Update GMP 4.2.3
* Updated the Msys/MinGW environment. I had to reinstall and it was a mess. 
* Updated the scripts to a single one that seems not to crash with cyg_heap
   commit exception. (less FDs required)

0.8.6
* Update SDK to latest SVN 2418
* Some tweak on the SDK

0.8.5
* Updated PSPLINKUSB
* patch PSPLINKUSB to support BIG MEMORY
* Update SDK to latest SVN 2413
* Debugging works (fully tested)
* Reduced dependency on cygwin (DLL packed with UPX)

0.8.4
* Upgrade MinGW GCC to 4.3.1
* Patched newlib int == int32_t (reduces compile errors) instead of
  long == int32_t. Since PSP is a 32bit machine both are valid options but
  int make it more natural.
* updated SDK to latest SVN 
  
0.8.3
* Split installer into 2 packages with doc/without doc for size reasons
* Test the compiler by compiling all the samples in the TC script
* Vista Support
* Upgrade MinGW GCC to 4.3.0, this forces the GDB to be build with -Werror
  disabled.

0.8.2
* GCC 4.3.0 & GDB 6.8 are the base versions from now on.

0.7.4
* Sync to SVN 2387
 - Added sceUtilityLoadModule() and sceUtilityUnloadModule().
 - Added the remaining stubs and prototypes for sceAudio*, found from various
   sources including cooleyes, lteixeira, Saotome, cswindle, Fanjita,
   SilverSpring.

0.7.3
* Sync to SVN 2385
* HTTP Browser support added to SDK

0.8.1
* GCC 4.3.0
* GDB 6.8

0.7.2
* Sync to PS2DEV SVN
* Reduce differences between MinPSPW patches and Official patches

0.7.1
* builds ASM files without errors due to bad make
* added true.exe for makefile assertions
* GDB was kept out of 0.7 by mistake

0.7
* Removed the dependency on groff, less, cp, mkdir, rm on the script,
  now they are downloaded from the internet
* Added patch for GCC to accept: -mpreferred-stack-boundary=#
* update to SVN 2377
* PS2DEV toolchain patches are downloaded from the internet, so no
  need to keep then sync with this TC
* Update usbpsplink to latest SVN
* No input required during all TC script, all configs are
  - SourceForge MIRROR url
  - SVN host for PS2DEV
  - target dir (c:/pspsdk)

0.6
* Removed the dependency for the env var PSPSDK
* Fixed psp-config
* Better vsmake.bat
* Better man.bat
* Fixed issue that some installations would end up without env vars due to
  delayed hdd writes.
* No need to hack SDK makefiles anymore
* GNU tools (cp, rm, mkdir, sed) called with the original names no need to
  append a "2"

0.5
* First good release
* Started the concept of DEVPAKs


===============================================================================
 What's different?
===============================================================================
 
The main difference is that this is a native cross compiler for Microsoft
Windows Operating Systems.
  
Second, you can run it directly from a DOS Command Prompt BOX or from your
favorite IDE (Eclipse and Visual Studio Express tested)
  
===============================================================================
 Where do I go from here?
===============================================================================

Visit the following sites to learn more:

http://www.ps2dev.org
http://forums.ps2dev.org

My MINGW specific stuff:
http://www.jetdrone.com

===============================================================================
 How to build it myself (new way) ?
===============================================================================

Download mingw-get tool from sourceforge.net/projects/mingw

Once you have it install it to: C:\MinGW\bin, open a DOS box and run:

# update the current reppo info
mingw-get update
# install the base system
mingw-get install gcc g++ msys-base msys-wget msys-unzip \
  mingw-developer-toolkit mingw32-libiconv mingw32-pthreads-w32 \
  mingw32-gmp mingw32-mpfr msys-texinfo
  
at this point you can start msys console (C:\MinGW\msys\1.0\msys.bat)

Unfortunately not all dependencies are on mingw-get so you need to install
by hand:

  - doxygen 1.7.3
    http://ftp.stack.nl/pub/users/dimitri/doxygen-1.7.3.windows.bin.zip
  - The following are in the wports folder
    * dot 1.16
	* unrar
  - svn 1.6.15
    http://subversion.apache.org

CMake get it from:
 http://www.cmake.org/files/v2.8/cmake-2.8.3-win32-x86.zip
  install to /local

For pkg-config checks to work with autotools you need to copy:
  cp mingw/pkg.m4 /mingw/share/aclocal

===============================================================================
 How to build it myself (Old way) ?
===============================================================================

Initial builds were made in a custom Msys/MinGW environment. Keeping this env
up to date was a terrible task since there were conflicts constantly between
updated dlls and tools.

1st Download latest MinGW version and install it:

Maintaining a working native toolchain is hard, so I have decided to go with
the old stable builds instead of bleeding edge test releases. To start
download the mingw installer. At the time of writting of this mini howto it is
version 5.1.6 and install the current mingw into C:\msys\mingw. The
installation should consist of C and C++ compiler, do not include the make
tool. You can install other compilers if you want but they are not required for
building the cross compiler.

Download and unzip over c:\msys\mingw.

Optionally install GDB
http://downloads.sourceforge.net/mingw/gdb-7.0-2-mingw32-bin.tar.gz

2nd Download and install MSYS Developer Toolkit executable:
http://downloads.sourceforge.net/mingw/msysDTK-1.0.1.exe
Install to c:\msys.

3rd Download latest MSYS and install it:
http://prdownloads.sourceforge.net/mingw/MSYS-1.0.11.exe
Chose c:\msys as installation directory. Leave all other options unchanged.
During the postinstall script, please carefully answer all questions. 
Important: Do not skip questions with enter.

Note: Users of 64-bit Windows variants have to change the startmenu shortcut.
Change it to c:\WINDOWS\SysWOW64\cmd.exe /C c:\dev\msys\msys.bat (adjust path
to Windows directory as needed)

At this moment you have a working bash shell with the basic tools, however
to make it more convenient we need some extra libs and tools.

4th Download wget:
http://prdownloads.sourceforge.net/gnuwin32/wget-1.11.4-1-bin.zip
http://prdownloads.sourceforge.net/gnuwin32/wget-1.11.4-1-dep.zip
Unzip to C:\msys\local

5th Download the following files to your local home, open the MSys shell and
execute:
wget http://downloads.sourceforge.net/mingw/m4-1.4.13-1-msys-1.0.11-bin.tar.lzma
wget ftp://ftp.gnu.org/gnu/libtool/libtool-2.2.6a.tar.gz 
wget ftp://ftp.gnu.org/gnu/autoconf/autoconf-2.64.tar.bz2
wget ftp://ftp.gnu.org/gnu/automake/automake-1.10.2.tar.bz2

6th install the download software:
cd /
m4-1.4.13-1-msys-1.0.11-bin.tar.lzma

cd ~
tar -xvzf libtool-2.2.6a.tar.gz
cd libtool-2.2.6
./configure --prefix=/usr
make
make install

cd ~
tar -xvjf autoconf-2.64.tar.bz2
cd autoconf-2.64
./configure --prefix=/usr
make
make install

cd ~
tar -xvjf automake-1.10.2.tar.bz2
cd automake-1.10.2
./configure --prefix=/usr
make
make install

7th Install other packages we need (into C:\msys\local)
  - doxygen 1.5.7.1
    http://ftp.stack.nl/pub/users/dimitri/doxygen-1.5.7.1.windows.bin.zip
  - The following are in the wports folder
    * pod2man
    * dot 1.16
	* unrar
	* unzip
  - svn 1.6.5
    http://subversion.tigris.org

8th Install Python 2.5.4 (later may work but not tested)
  http://python.org/ftp/python/2.6.5/python-2.6.5.msi
  - Python 2.6.5 (Use the windows installer) Then add to the PATH
  - Add it to the MSys PATH by adding the line:
     SET PATH=%PATH%;C:\Python25
    In the beginning of the MSYS.BAT file

9th Some dev packs need bison since I've to patch some yy files,
get them from the mingw msys project:
  -flex-2.5.35-1-msys-1.0.11-bin.tar.lzma
    * Extract "over" the MSYS installation.
  - bison-2.4.1-1-msys-1.0.11-bin.tar.lzma
    * Extract "over" the MSYS installation.
  - libregex-0.12-1-msys-1.0.11-dll-0.tar.lzma
    * Extract "over" the MSYS installation.
	* Then rename to msys-regex-1.dll

10th CMake get it from:
 http://www.cmake.org/files/v2.8/cmake-2.8.1-win32-x86.zip
  install to /local

11th Aparently the current bash causes bugs with autotools during SDL_mixer
build, for this we need to update the following packages into /msys/bin
  - bash-3.1.17-3-msys-1.0.13-bin.tar.lzma
  - libregex-1.20090805-2-msys-1.0.13-dll-1.tar.lzma
  - libtermcap-0.20050421_1-2-msys-1.0.13-dll-0.tar.lzma

To build run the toolchain script:

./toolchain.sh

===============================================================================
 How to build it myself (Ubuntu)?
===============================================================================

## Install the required packages.
 sudo apt-get install build-essential autoconf automake bison flex \
  libncurses5-dev libreadline-dev libusb-dev texinfo subversion doxygen \
  graphviz libtool unrar unzip cmake wget pkg-config

## it is required to use the static mpfr and gmp otherwise ubuntu 10.04 LTS
 binaries are not compatible with 10.10 or above and maybe with other distros.
 
 This means that the toolchain script now builds this 2 dependencies too.
 
## Build and install the toolchain + sdk.
 ./toolchain.sh


===============================================================================
 How to build it myself (Ubuntu 64bit)?
===============================================================================

It just works as with 32bit Ubuntu.

===============================================================================
 How to build it myself (Ubuntu 64bit targetting 32bit Ubuntu)?
===============================================================================

If you really need this, say you only have a 64bit machine but want to make a
32bit sdk say to run on your netbook.

1st install required packages:
 sudo apt-get install dchroot debootstrap

2nd create the environment config
 sudo nano /etc/schroot/schroot.conf and add:

  [maverick32]
  type=directory
  description=Ubuntu Maverick 32bit
  directory=/chroot/maverick32
  priority=3
  users=<your user>
  groups=<your user>
  root-groups=root
  personality=linux32

3rd create the chroot directory
 mkdir -p /chroot/maverick32

4th bootstrap the chroot environment
 sudo debootstrap --variant=buildd --arch=i386 maverick \
  /chroot/maverick32 http://<your closest ubuntu mirror>/ubuntu/

5th If you are using an encrypted home you need to change
 /etc/schroot/mount-defaults and add:
  /home/<username>	/home/<username>	none	rw,bind	0	0

6th enter the chroot environment and install add the software as described
 above
  sudo schroot -c maverick32
  sudo apt-get install ...
  ./toolchain.sh

7th If you use the encrypted home, you need to build from outside your home
 because for some unknown reason to me, it does not build from encryptfs
 home's.

===============================================================================
 How to build it myself (OpenSolaris)?
===============================================================================

Install required packages:
pfexec pkg install gcc-dev-4 gcc-432 SUNWbison SUNWaconf SUNWgnu-automake-110 \
    SUNWlibtool
You also need unrar from rarlabs for solaris to build OSlib and readline for
the pspsh, usbhostfs_pc and remotejoy

I've uploaded a working readline lib to jucr.opensolaris.org so if I get
enough votes it will become available on the contrib repository.

===============================================================================
 How to build it myself (MacOSX)?
===============================================================================

Install required packages using macports.org:
 * autoconf
 * automake
 * bison
 * flex
 * ncurses
 * readline
 * libusb
 * texinfo
 * libgmp3
 * libmpfr
 * subversion
 * doxygen
 * graphviz
 * libtool
 * unrar
 * unzip
 * cmake
 * wget
 * SDL

Once you have all these dependencies installed just run the toolchain script.

Note: I don't own a Mac or have access to one, so all this info is provided
"as is". The script has been tested by the community and updated with the
community feedback. A special thanks for Diogo Autilio the tester of these
changes.

===============================================================================
 Utils commands
===============================================================================

awk '{ sub("\r$", ""); print }' dosfile.txt > unixfile.txt
awk 'sub("$", "\r")' unixfile.txt > dosfile.txt
```
