#!/bin/sh
# Type a script or drag a script file from your workspace to insert its path.
echo "Run script for copy file!!! by shinichi inoue"

if [ -d "$BUILD_DIR/Debug" ]; then
    cp "$SRCROOT"/../External/glew/"2.2.0_1"/lib/*.dylib $BUILD_DIR/Debug
    cp "$SRCROOT"/../External/sdl2/"2.0.22"/lib/*.dylib $BUILD_DIR/Debug
    cp "$SRCROOT"/../External/sdl2_image/"2.6.0_1"/lib/*.dylib $BUILD_DIR/Debug
    cp "$SRCROOT"/../External/SOIL/lib/*.dylib $BUILD_DIR/Debug
    cp "$SRCROOT"/../External/FMOD/"FMOD Programmers API"/api/lowlevel/lib/*.dylib $BUILD_DIR/Debug
    cp "$SRCROOT"/../External/FMOD/"FMOD Programmers API"/api/studio/lib/*.dylib $BUILD_DIR/Debug
fi

if [ -d "$BUILD_DIR/Release" ]; then
    cp "$SRCROOT"/../External/glew/"2.2.0_1"/lib/*.dylib $BUILD_DIR/Release
    cp "$SRCROOT"/../External/sdl2/"2.0.22"/lib/*.dylib $BUILD_DIR/Release
    cp "$SRCROOT"/../External/sdl2_image/"2.6.0_1"/lib/*.dylib $BUILD_DIR/Release
    cp "$SRCROOT"/../External/SOIL/lib/*.dylib $BUILD_DIR/Release
    cp "$SRCROOT"/../External/FMOD/"FMOD Programmers API"/api/lowlevel/lib/*.dylib $BUILD_DIR/Release
    cp "$SRCROOT"/../External/FMOD/"FMOD Programmers API"/api/studio/lib/*.dylib $BUILD_DIR/Release
fi
    
    

