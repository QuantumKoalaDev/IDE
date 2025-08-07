cmake_minimum_required(VERSION 3.20)
project(IDE LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# External libraries
add_subdirectory(external/freetype EXCLUDE_FROM_ALL)

# GLEW manually integrated
set(GLEW_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/external/glew-2.2.0/include")

# UI
# file(GLOB_RECURSE UI_SOURCE CONFIGURE_DEPENDS
#     "${CMAKE_SOURCE_DIR}/src/UI/*.cpp"
#     "${CMAKE_SOURCE_DIR}/src/UI/*.h"
# )

# add_library(IDEUI STATIC ${UI_SOURCE})

# target_include_directories(IDEUI PUBLIC "${GLEW_INCLUDE_DIR}")

# Core
file(GLOB_RECURSE CORE_SOURCE CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/Core/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/Core/*.h"
)

# Application
file(GLOB_RECURSE APPLICATION_SOURCE CONFIGURE_DEPENS
    "${CMAKE_SOURCE_DIR}/src/Application/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/Application/*.h"
)

add_library(IDECORE STATIC ${CORE_SOURCE})
add_library(IDEApplication ${APPLICATION_SOURCE})

target_link_libraries(IDEApplication PRIVATE IDECORE)


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
    # find_package(X11 REQUIRED)
    # target_link_libraries(IDEUI PUBLIC GL freetype GLEW ${X11_LIBRARIES})
    # target_include_directories(IDEUI PUBLIC ${X11_INCLUDE_DIR})
endif()

target_include_directories(IDECORE PUBLIC
    ${CMAKE_SOURCE_DIR}/src
)
target_include_directories(IDEApplication PUBLIC
    ${CMAKE_SOURCE_DIR}/src
)

# Main executable
# add_executable(IDE.out src/Application/main.cpp)
add_executable(IDE.out src/main.cpp)



if(WIN32)
    set_target_properties(IDE.out PROPERTIES
        VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
    )
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT IDE.out)

    foreach(source IN LISTS UI_SOURCE)
        file(RELATIVE_PATH relPath "${CMAKE_SOURCE_DIR}/src/UI" "${source}")
        get_filename_component(dir "${relPath}" DIRECTORY)
        string(REPLACE "/" "\\" filterPath "${dir}")
        source_group("${filterPath}" FILES "${source}")
    endforeach()
    
endif()

# target_link_libraries(IDE.out PRIVATE IDEUI)
target_link_libraries(IDE.out PRIVATE IDECORE)
target_link_libraries(IDE.out PRIVATE IDEApplication)
