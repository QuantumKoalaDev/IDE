cmake_minimum_required(VERSION 3.20)
project(IDE LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Precompiled Header helper
# include(cmake/PCH.cmake)

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


# External libraries
add_subdirectory(external/freetype EXCLUDE_FROM_ALL)

# GLEW manually integrated
set(GLEW_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/external/glew-2.2.0/include")

# UI
add_library(IDEUI STATIC
    src/UI/Window/OpenGLWindow.cpp
    src/UI/Window/OpenGLWindow.h
    src/UI/Toolbar/Toolbar.cpp
    src/UI/Toolbar/Toolbar.h
    src/UI/Renderer/FontRenderer/FontRenderer.cpp
    src/UI/Renderer/FontRenderer/FontRenderer.h
    src/UI/Textbox/Textbox.cpp
    src/UI/Textbox/Textbox.h
)

target_include_directories(IDEUI PUBLIC "${GLEW_INCLUDE_DIR}")

# Static Lib !Important: just works after seperate glew build -> execute 'make' in glew external/glew-2.2.0!
if(WIN32)
    target_compile_definitions(IDEUI PUBLIC GLEW_STATIC)
    set(GLEW_LIBRARY "${CMAKE_SOURCE_DIR}/external/glew-2.2.0/lib/Release/x64/glew32s.lib")
else()
    set(GLEW_LIBRARY "${CMAKE_SOURCE_DIR}/external/glew-2.2.0"/lib/libGLEW.a)
    add_library(GLEW STATIC IMPORTED GLOBAL)
    set_target_properties(GLEW PROPERTIES
        IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/external/glew-2.2.0/lib/libGLEW.a"
        INTERFACE_INCLUDE_DIRECTORIES "${GLEW_INCLUDE_DIR}"
    )
endif()

# Platform specific OpenGL and windowing dependencies
if(WIN32)
    target_link_libraries(IDEUI PUBLIC opengl32 freetype ${GLEW_LIBRARY})
else()
    find_package(X11 REQUIRED)
    target_link_libraries(IDEUI PUBLIC GL freetype GLEW ${X11_LIBRARIES})
    target_include_directories(IDEUI PUBLIC ${X11_INCLUDE_DIR})
endif()

# Main executable
add_executable(IDE.out src/main.cpp)

if(WIN32)
    set_target_properties(IDE.out PROPERTIES
        VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
    )
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT IDE.out)
endif()

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