cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=gnu++11")

set(SRC "../../../../../Bug Sprint/Source")

add_library(app-glue STATIC
    ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c
)

include_directories(
    "${SRC}/Graphics Utils"
)

add_library(bug-sprint SHARED
    "${SRC}/Android Layer/Main.cpp"
    "${SRC}/Android Layer/CoreAdapter.cpp"
    "${SRC}/Graphics Utils/Color.cpp"
)

target_include_directories(bug-sprint PRIVATE
    ${ANDROID_NDK}/sources/android/native_app_glue
)

target_link_libraries(bug-sprint
    android
    app-glue
    log
    EGL
    GLESv2
)