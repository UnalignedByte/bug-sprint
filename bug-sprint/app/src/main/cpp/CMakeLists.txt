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
    "${SRC}/Graphics Utils/2D"
    "${SRC}/Graphics Utils/3D"
    "${SRC}/Game"
    "${SRC}/Game/Things"
)

add_library(bug-sprint SHARED
    "${SRC}/Android Layer/Main.cpp"
    "${SRC}/Android Layer/CoreAdapter.cpp"
    "${SRC}/Android Layer/SystemUtils.cpp"

    "${SRC}/Utils/File.cpp"
    "${SRC}/Utils/FileBuffer.cpp"

    "${SRC}/Graphics Utils/Color.cpp"
    "${SRC}/Graphics Utils/ShaderProgram.cpp"
    "${SRC}/Graphics Utils/Texture.cpp"
    "${SRC}/Graphics Utils/Image.cpp"
    "${SRC}/Graphics Utils/Instance.cpp"
    "${SRC}/Graphics Utils/RenderPass.cpp"
    "${SRC}/Graphics Utils/Scene.cpp"

    "${SRC}/Graphics Utils/3D/Instance3D.cpp"
    "${SRC}/Graphics Utils/3D/Drawable.cpp"
    "${SRC}/Graphics Utils/3D/Model.cpp"
    "${SRC}/Graphics Utils/3D/Camera.cpp"
    "${SRC}/Graphics Utils/3D/Light.cpp"
    "${SRC}/Graphics Utils/3D/ShadedRenderPass.cpp"
    "${SRC}/Graphics Utils/3D/ShadowRenderPass.cpp"
    "${SRC}/Graphics Utils/3D/SkyboxRenderPass.cpp"

    "${SRC}/Graphics Utils/2D/Instance2D.cpp"
    "${SRC}/Graphics Utils/2D/RenderPass2D.cpp"
    "${SRC}/Graphics Utils/2D/Sprite.cpp"
    "${SRC}/Graphics Utils/2D/Button.cpp"
    "${SRC}/Graphics Utils/2D/DebugSprite.cpp"

    "${SRC}/Game/Core.cpp"
    "${SRC}/Game/TestScene.cpp"
    "${SRC}/Game/CarScene.cpp"
    "${SRC}/Game/Things/Car.cpp"
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