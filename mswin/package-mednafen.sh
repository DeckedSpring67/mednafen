#!/bin/bash
VERSION=`head -n 1 ../Documentation/modules.def`

cd build64 && \
cp ../../src/mednafen.exe . && \
x86_64-w64-mingw32-strip mednafen.exe && \
x86_64-w64-mingw32-strip libstdc++-6.dll libcharset-1.dll libiconv-2.dll libFLAC-8.dll libogg-0.dll libsndfile-1.dll libvorbis-0.dll libvorbisenc-2.dll libSDL2-2-0-0.dll && \
mkdir -p de/LC_MESSAGES ru/LC_MESSAGES && \
cp ../../po/de.gmo de/LC_MESSAGES/mednafen.mo && \
cp ../../po/ru.gmo ru/LC_MESSAGES/mednafen.mo && \
7za a mednafen-"$VERSION"-win64.zip mednafen.exe libgcc_s_seh-1.dll libstdc++-6.dll libcharset-1.dll libiconv-2.dll libFLAC-8.dll libogg-0.dll libsndfile-1.dll libvorbis-0.dll libvorbisenc-2.dll libSDL2-2-0-0.dll zlib1.dll de/ ru/ && \
mv mednafen-"$VERSION"-win64.zip ../
cd .. && \
7za a mednafen-"$VERSION"-win64.zip COPYING ChangeLog Documentation/*.html Documentation/*.css Documentation/*.png Documentation/*.txt && \
cd ..

