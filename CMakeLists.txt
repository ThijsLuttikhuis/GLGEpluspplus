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
set(CMAKE_CXX_FLAGS "-O0 -Wall -Wextra")
#set(CMAKE_CXX_FLAGS_DEBUG "-O0 -Wall -Wextra")
#set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wnone")

set(MESH_DIR
		src/window/mesh/Mesh.cpp
		src/window/mesh/Mesh.h
		src/window/mesh/ColorMesh.cpp
		src/window/mesh/ColorMesh.h
		src/window/mesh/TextureMesh.cpp
		src/window/mesh/TextureMesh.h
		)

set(SHADER_DIR
		src/window/shader/Shader.cpp
		src/window/shader/Shader.h
		src/window/shader/TextureShader.cpp
		src/window/shader/TextureShader.h
		src/window/shader/ColorShader.cpp
		src/window/shader/ColorShader.h
		)

set(WINDOW_DIR
		src/window/Window.cpp
		src/window/Window.h
		src/window/Camera.cpp
		src/window/Camera.h

		${MESH_DIR}
		${SHADER_DIR}
		)

set(INPUT_DIR
		src/input/KeyboardInput.cpp
		src/input/KeyboardInput.h
		src/input/MouseInput.cpp
		src/input/MouseInput.h
		)

set(OBJECTS_DIR

		src/objects/PhysicsBody.cpp
		src/objects/PhysicsBody.h
        src/input/Input.cpp
		src/input/Input.h
		src/objects/Interactions/Interaction.cpp
		src/objects/Interactions/Interaction.h
		src/objects/Interactions/ConstantForce.cpp
		src/objects/Interactions/ConstantForce.h
        src/window/mesh/HeightMapMesh.cpp
		src/window/mesh/HeightMapMesh.h src/objects/HeightMapBody.cpp src/objects/HeightMapBody.h src/objects/utils/HeightMap.cpp src/objects/utils/HeightMap.h src/objects/Interactions/FloorInteraction.cpp src/objects/Interactions/FloorInteraction.h src/objects/utils/PerlinNoiseHeightMap.cpp src/objects/utils/PerlinNoiseHeightMap.h src/window/PosAngle.cpp src/window/PosAngle.h)

# make executable
add_executable(GLGEplusplus
		src/main.cpp
		${WINDOW_DIR}
		${OBJECTS_DIR}
		${INPUT_DIR}


		src/TEMP.h
		)

target_link_libraries(GLGEplusplus
		${OPENGL_LIBRARY}
		glfw
		GLEW_1130
		)