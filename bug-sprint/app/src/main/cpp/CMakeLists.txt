cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=gnu++14")

set(SRC "../../../../../Bug Sprint/Source")

add_library(app-glue STATIC
    ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c
)

include_directories(
    "${SRC}/Android Layer"
    "${SRC}/Utils"
    "${SRC}/Graphics Utils"
    "${SRC}/Game"
)

add_library(bug-sprint SHARED
    "${SRC}/Android Layer/Main.cpp"
    "${SRC}/Android Layer/CoreAdapter.cpp"
    "${SRC}/Android Layer/SystemUtils.cpp"

    "${SRC}/Utils/File.cpp"
    "${SRC}/Utils/FileBuffer.cpp"

    "${SRC}/Graphics Utils/Color.cpp"
    "${SRC}/Graphics Utils/Model.cpp"
    "${SRC}/Graphics Utils/ShaderProgram.cpp"
    "${SRC}/Graphics Utils/Image.cpp"
    "${SRC}/Graphics Utils/Texture.cpp"

    "${SRC}/Game/Core.cpp"
    "${SRC}/Game/Instance.cpp"
    "${SRC}/Game/Drawable.cpp"
    "${SRC}/Game/Camera.cpp"
    "${SRC}/Game/Light.cpp"
)

target_include_directories(bug-sprint PRIVATE
    ${ANDROID_NDK}/sources/android/native_app_glue
)

target_link_libraries(bug-sprint
    android
    app-glue
    jnigraphics
    log
    EGL
    GLESv3
)