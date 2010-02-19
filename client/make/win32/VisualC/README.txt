To build the Atrinik client with Visual C++, you will need to:

1. Run Setup.bat or Setup_x64.bat, which will unpack the tar.gz
   files and place the required dlls in main directory.
   
   Setup.bat will unpack the 32-bit dll files, while
   Setup_x64.bat will unpack the 64-bit dll files. Do not run
   both batch files, as the dll files from one will be
   overwritten with the files from the other.

   If you are unsure on which batch file to run, just run the
   regular Setup.bat for the 32-bit installation as it will work
   in both the 32-bit and 64-bit editions of Windows. Also, the
   64-bit client is very much in testing at the moment.

2. Double click on Atrinik.sln to open the project.

3. Select build configuration. This should be Win32 if you used
   Setup.bat or x64 if you ran Setup_x64.bat.

4. Build solution.

----------------------------------------------------------------

Below are a list of dependencies and their versions for
reference. It's best to include them here so that we know when
they should be updated, and it makes it easier to find out
whether or not specific versions are compatible with each other.

SDL:       1.2.14
SDL_image: 1.2.10
SDL_mixer: 1.2.11
zlib:      1.2.3
libpng:    1.4.0  (used by SDL_image)
libogg:    1.1.4  (used by SDL_mixer)
libvorbis: 1.2.3  (used by SDL_mixer)