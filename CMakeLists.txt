cmake_minimum_required(VERSION 3.20)
project(IDE LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Precompiled Header helper
# include(cmake/PCH.cmake)

# External libs
# add_subdirectory(external/imgui)

# Core lib
# add_library(IDECore STATIC
#     src/Core/... cpp
#     src/Core/ ... cpp
# )
# target_include_directories(MyAppCore PUBLIC include)
# enable_pch(MyAppCore src/Core/pch.hpp)

# Backend
# add_library(MyAppBackend STATIC
#     src/Backend/Backend.cpp
#     src/Backend/Backend.hpp
# )
# target_link_libraries(MyAppBackend PUBLIC MyAppCore)
# target_include_directories(MyAppBackend PUBLIC include)
# enable_pch(MyAppBackend src/Backend/pch.hpp)

# UI
add_library(IDEUI STATIC
    src/UI/Window/OpenGLWindow.cpp
    src/UI/Window/OpenGLWindow.h
    src/UI/Toolbar/Toolbar.cpp
    src/UI/Toolbar/Toolbar.h
    src/UI/Renderer/FontRenderer/FontRenderer.cpp
    src/UI/Renderer/FontRenderer/FontRenderer.h
)
find_package(Freetype REQUIRED)
target_include_directories(IDEUI PUBLIC ${FREETYPE_INCLUDE_DIRS})
target_link_libraries(IDEUI PUBLIC GL GLEW X11 ${FREETYPE_LIBRARIES})
# target_link_libraries(MyAppUI PUBLIC MyAppCore imgui)
# target_include_directories(MyAppUI PUBLIC include)
# enable_pch(MyAppUI src/UI/pch.hpp)

# Main executable
add_executable(IDE.out src/main.cpp)
target_link_libraries(IDE.out PRIVATE IDEUI)
# target_link_libraries(MyApp PRIVATE MyAppCore MyAppBackend MyAppUI)


# Beispiel enable_pch() Funktion (cmake/PCH.cmake)

# function(enable_pch TARGET PCH_FILE)
#     if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
#         target_precompile_headers(${TARGET} PRIVATE "${PCH_FILE}")
#     elseif (MSVC)
#         target_precompile_headers(${TARGET} PRIVATE "${PCH_FILE}")
#     endif()
# endfunction()