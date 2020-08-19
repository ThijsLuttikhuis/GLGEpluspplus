cmake_minimum_required (VERSION 3.0)
project (GLGEplusplus)

find_package(OpenGL REQUIRED)


# Compile external dependencies 
add_subdirectory(external)
if(INCLUDE_DISTRIB)
	add_subdirectory(distrib)
endif(INCLUDE_DISTRIB)

include_directories(
	external/AntTweakBar-1.16/include/
	external/glfw-3.1.2/include/
	external/glm-0.9.7.1/
	external/glew-1.13.0/include/
	external/assimp-3.0.1270/include/
	external/bullet-2.81-rev2613/src/
)

add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

# set flags
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wnone")

set(WINDOW_DIR
		src/window/Window.cpp
		src/window/Window.h
		src/window/Camera.cpp
		src/window/Camera.h
		)

set(INPUT_DIR
		src/input/KeyboardInput.cpp
		src/input/KeyboardInput.h
		src/input/MouseInput.cpp
		src/input/MouseInput.h
        )



# make executable
add_executable(GLGEplusplus
		src/main.cpp

		${WINDOW_DIR}
		${INPUT_DIR}
		)

target_link_libraries(GLGEplusplus
		${OPENGL_LIBRARY}
		glfw
		GLEW_1130
		)