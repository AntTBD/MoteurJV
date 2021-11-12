cmake_minimum_required(VERSION 3.20)

#################################
# Variables
#################################
set(PROJECT_NAME MoteurJV)
set(IMGUI_VERSION 1.85)
set(USE_SRC_FILES true)
#################################

set(CMAKE_SYSTEM_VERSION 10.0 CACHE STRING "" FORCE)

project(MoteurJV
        VERSION 2.0
        DESCRIPTION "UQAC Project - Physique Engine"
        LANGUAGES C CXX)

################################################################################
# Set target arch type if empty. Visual studio solution generator provides it.
################################################################################
if(NOT CMAKE_VS_PLATFORM_NAME)
    set(CMAKE_VS_PLATFORM_NAME "x64")
endif()
message("${CMAKE_VS_PLATFORM_NAME} architecture in use")

if(NOT ("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86"
     OR "${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32"
     OR "${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64"))
    message(FATAL_ERROR "${CMAKE_VS_PLATFORM_NAME} arch is not supported!")
endif()

################################################################################
# Global configuration types
################################################################################
set(CMAKE_CONFIGURATION_TYPES
        "Debug"
        "Release"
        CACHE STRING "" FORCE
        )


################################################################################
# Source files
################################################################################


# imgui
file(GLOB ImGuiFiles CONFIGURE_DEPENDS include/imgui-${IMGUI_VERSION}/imgui*.c*)
file(GLOB ImGuiGLFWFiles CONFIGURE_DEPENDS include/imgui-${IMGUI_VERSION}/backends/imgui_impl_glfw*.c*)
file(GLOB ImGuiOpenGL3Files CONFIGURE_DEPENDS include/imgui-${IMGUI_VERSION}/backends/imgui_impl_opengl3*.c*)

# glad
file(GLOB_RECURSE glad CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/include/glad/include/*.c*)

# include du dossier avec tous les fichiers sources
if(${USE_SRC_FILES})
    # recherche de tous les fichiers en .cpp dans le dossier src de manière récurssive
    file(GLOB_RECURSE myListOfSourcesFiles CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c*)
endif()
#else()
    # recherche de tous les fichiers en .cpp dans le dossier principal
    file(GLOB myListOfOriginalSourcesFiles CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.c*)
#endif()

file(GLOB shaders CONFIGURE_DEPENDS shaders/*)


set(ALL_FILES
        ${glad}
        ${ImGuiFiles}
        ${ImGuiGLFWFiles}
        ${ImGuiOpenGL3Files}
        ${shaders}
        ${myListOfOriginalSourcesFiles}
        ${myListOfSourcesFiles}
)

macro(print_all_variables)
    message(STATUS "print_all_variables------------------------------------------{")
    get_cmake_property(_variableNames VARIABLES)
    foreach (_variableName ${_variableNames})
        message(STATUS "${_variableName}=${${_variableName}}")
    endforeach()
    message(STATUS "print_all_variables------------------------------------------}")
endmacro()

print_all_variables()
################################################################################
# Target
################################################################################
add_executable(${PROJECT_NAME}
        ${glad}
        ${ImGuiFiles}
        ${ImGuiGLFWFiles}
        ${ImGuiOpenGL3Files}
        ${myListOfOriginalSourcesFiles}
        ${myListOfSourcesFiles}
        )

################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_DIRECTORY_DEBUG   "${CMAKE_CURRENT_SOURCE_DIR}//build/$<CONFIG>/"
    OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}//build/$<CONFIG>/"
)
set_target_properties(${PROJECT_NAME} PROPERTIES
    INTERPROCEDURAL_OPTIMIZATION_DEBUG   "FALSE"
    INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
)

################################################################################
# Include directories
################################################################################
target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include/glad/include;"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/glm-0.9.9.8;"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/imgui-${IMGUI_VERSION};"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/imgui-${IMGUI_VERSION}/backends;"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/imgui-${IMGUI_VERSION}/examples/libs/glfw/include"
)


################################################################################
# Dependencies
################################################################################
set(ADDITIONAL_LIBRARY_DEPENDENCIES
    "opengl32;"
    "glfw3"
)
target_link_libraries(${PROJECT_NAME} PRIVATE "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86"
        OR "${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    target_link_directories(${PROJECT_NAME} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/include/imgui-${IMGUI_VERSION}/examples/libs/glfw/lib-vc2010-32"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_link_directories(${PROJECT_NAME} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/include/imgui-${IMGUI_VERSION}/examples/libs/glfw/lib-vc2010-64"
    )
endif()
