cmake_minimum_required(VERSION 3.21)

project(MScProject)

set(CMAKE_CXX_STANDARD 17)
# static libraries please
set(BUILD_SHARED_LIBS FALSE)
# make executable run in project's root directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})

# FetchContent to fetch git repos remotely
include(FetchContent)

#-----------------------------
# External libraries from git repos
#-----------------------------
# glfw
set(GLFW_BUILD_DOCS OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_EXAMPLES OFF)
FetchContent_Declare(glfw GIT_REPOSITORY https://github.com/glfw/glfw.git GIT_TAG 3.3.6)
FetchContent_MakeAvailable(glfw)
#-----------------------------
# Dear ImGui
FetchContent_Declare(imgui GIT_REPOSITORY https://github.com/ocornut/imgui.git GIT_TAG origin/docking)
FetchContent_MakeAvailable(imgui)
add_subdirectory("subfolder/ImGui Cmake")
#-----------------------------
# GLM
FetchContent_Declare(glm GIT_REPOSITORY https://github.com/g-truc/glm.git GIT_TAG 0.9.9.8)
FetchContent_MakeAvailable(glm)
add_compile_definitions(GLM_FORCE_LEFT_HANDED)
#-----------------------------
# glew
set(glew-cmake_BUILD_SHARED OFF)
set(USE_GLU "Use GLU" ON)
FetchContent_Declare(glew GIT_REPOSITORY https://github.com/Perlmint/glew-cmake.git GIT_TAG glew-cmake-2.2.0)
FetchContent_MakeAvailable(glew)
#-----------------------------

#-----------------------------
# IMPORTANT SECTION! Source code
#-----------------------------
# New place to put all your source code files into:
set(PROJECT_SOURCES_WITHOUT_MAIN
	# order by folder structure
    "Source/Mesh/mesh.cpp;"
	
	"Source/Interface.cpp;"

	"Source/Algorithm/scene.cpp;"
	"Source/Algorithm/inspector.cpp;"
	"Source/Algorithm/simplification.cpp;"
)

add_executable(${PROJECT_NAME} Source/main.cpp ${PROJECT_SOURCES_WITHOUT_MAIN})
#-----------------------------

#-----------------------------
# IMPORTANT SECTION! Include files
#-----------------------------
# list of folders to include
set(PROJECT_INCLUDES
	"Include;"
	)
	
# different targets
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_INCLUDES})
#-----------------------------

#-----------------------------
# Linking libraries
#-----------------------------
# list of libraries we're using in the main engine
set(PROJECT_LIBRARIES
	"glfw;"
	"imgui;"
	"glm;"
	"libglew_static;"
  )

# different targets
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_LIBRARIES})
#-----------------------------

