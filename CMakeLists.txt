PROJECT(EFIE2D)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8 FATAL_ERROR)

# Add Git info to the executable
# Get the current working branch tag
IF(EXISTS "${CMAKE_SOURCE_DIR}/.git")
  EXECUTE_PROCESS(
    # COMMAND D:/Programs/Git/bin/git.exe rev-parse --abbrev-ref HEAD
    COMMAND D:/Programs/Git/bin/git.exe tag
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_TAG
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )

# Change accordingly the path to your Git installation
  EXECUTE_PROCESS(
    COMMAND D:/Programs/Git/bin/git.exe log -1 --format=%h
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_COMMIT_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )
ENDIF(EXISTS "${CMAKE_SOURCE_DIR}/.git")

message(STATUS "Git current tag: ${GIT_TAG}")
message(STATUS "Git commit hash: ${GIT_COMMIT_HASH}")

message(STATUS "Generating efie2d_version.h . . .")

CONFIGURE_FILE(
  ${CMAKE_SOURCE_DIR}/src/utils/efie2d_version.h.in
  ${CMAKE_SOURCE_DIR}/src/utils/efie2d_version.h
)

# # Define the EFIE2D src
SET(EFIE2D_SRC_SOLVER ${CMAKE_SOURCE_DIR}/src/solver/solver.cpp)
SET(EFIE2D_SRC_KERNEL ${CMAKE_SOURCE_DIR}/src/kernel/kernel.cpp)
SET(EFIE2D_SRC_AI_KERNEL ${CMAKE_SOURCE_DIR}/src/kernel/ai_ker.cpp)
SET(EFIE2D_TIMER ${CMAKE_SOURCE_DIR}/src/utils/hr_time.cpp)
SET(EFIE2D_SRC_JSON_READER ${CMAKE_SOURCE_DIR}/src/json_reader/json_reader.cpp)
SET(EFIE2D_SRC_MESH ${CMAKE_SOURCE_DIR}/src/mesh/mesh.cpp)
SET(EFIE2D_SRC_GEO ${CMAKE_SOURCE_DIR}/src/geometry/geometry.cpp)
SET(EFIE2D_SRC_MAT ${CMAKE_SOURCE_DIR}/src/material/material.cpp ${CMAKE_SOURCE_DIR}/src/material/dielectric_parameters.cpp)
SET(EFIE2D_SRC_OBJ ${CMAKE_SOURCE_DIR}/src/object/primitive_object.cpp)
SET(EFIE2D_SRC_MODEL ${CMAKE_SOURCE_DIR}/src/model/frequency.cpp ${CMAKE_SOURCE_DIR}/src/model/model.cpp)
SET(EFIE2D_SRC_EXC ${CMAKE_SOURCE_DIR}/src/excitation/excitation.cpp ${CMAKE_SOURCE_DIR}/src/excitation/planewave.cpp)

SET(EFIE2D_SRC ${EFIE2D_SRC_JSON_READER} ${EFIE2D_SRC_MAT} ${EFIE2D_SRC_OBJ} ${EFIE2D_SRC_MESH}
  ${EFIE2D_SRC_GEO} ${EFIE2D_SRC_MODEL} ${EFIE2D_SRC_EXC} ${EFIE2D_SRC_SOLVER} ${EFIE2D_SRC_KERNEL} ${EFIE2D_SRC_AI_KERNEL} ${EFIE2D_TIMER})
# Set folder for the Armadillo and Bessel/Hankel implementation
SET(Armadillo ${CMAKE_SOURCE_DIR}/Armadillo/armadillo-8.500.0)
SET(Bessel ${CMAKE_SOURCE_DIR}/ComplexBesselLib/complex_bessel-release-0.6)

# Define the include.
# Include all the EFIE2D /src
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src)
# Include armadillo src
INCLUDE_DIRECTORIES(${Armadillo}/include)
# Include Bessel src
INCLUDE_DIRECTORIES(${Bessel}/include)

# Link with the Armadillo library
LINK_DIRECTORIES(${Armadillo}/lib_win64)
# Link with the Bessel library
LINK_DIRECTORIES(${Bessel}/lib_win64)

# Add test executable target
ADD_EXECUTABLE(efie2d efie2d_main.cpp ${EFIE2D_SRC})

# Add the library to the main
TARGET_LINK_LIBRARIES(efie2d blas_win64_MT lapack_win64_MT complex_bessel)