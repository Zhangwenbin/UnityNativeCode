# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.18.1)

# Declares and names the project.

project("biz")

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
        biz

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        biz.c)

add_library( # Sets the name of the library.
        xhook

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        queue.h tree.h xh_core.h xh_core.c xh_elf.h xh_elf.c xh_errno.h xh_jni.c xh_log.c xh_log.h xh_util.c xh_util.h xh_version.c xh_version.h xhook.h xhook.c)

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
        log-lib
        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.
#target_include_directories(biz PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries( # Specifies the target library.
        xhook

        # Links the target library to the log library
        # included in the NDK.
        ${log-lib})

target_link_libraries(biz ${log-lib} xhook)
