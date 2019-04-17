PROJECT(EFIE2DTest)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8 FATAL_ERROR)

# Define the EFIE2D src
SET(EFIE2D_SRC_JSON_READER ${CMAKE_SOURCE_DIR}/../src/json_reader/json_reader.cpp)
SET(EFIE2D_SRC_MESH ${CMAKE_SOURCE_DIR}/../src/mesh/mesh.cpp)
SET(EFIE2D_SRC_GEO ${CMAKE_SOURCE_DIR}/../src/geometry/geometry.cpp)
SET(EFIE2D_SRC_MAT ${CMAKE_SOURCE_DIR}/../src/material/material.cpp ${CMAKE_SOURCE_DIR}/../src/material/dielectric_parameters.cpp)
SET(EFIE2D_SRC_OBJ ${CMAKE_SOURCE_DIR}/../src/object/primitive_object.cpp)
SET(EFIE2D_SRC_MODEL ${CMAKE_SOURCE_DIR}/../src/model/frequency.cpp ${CMAKE_SOURCE_DIR}/../src/model/model.cpp)
SET(EFIE2D_SRC_EXC ${CMAKE_SOURCE_DIR}/../src/excitation/excitation.cpp ${CMAKE_SOURCE_DIR}/../src/excitation/planewave.cpp)


# SET(EFIE2D_SRC_SOLVER ${CMAKE_SOURCE_DIR}/../src/solver/frequency.cpp ${CMAKE_SOURCE_DIR}/../src/solver/excitation.cpp ${CMAKE_SOURCE_DIR}/../src/solver/planewave.cpp ${CMAKE_SOURCE_DIR}/../src/solver/solver.cpp)
# SET(EFIE2D_SRC_KERNEL ${CMAKE_SOURCE_DIR}/../src/kernel/kernel.cpp)
# SET(EFIE2D_SRC_AI_KERNEL ${CMAKE_SOURCE_DIR}/../src/kernel/ai_ker.cpp)
# SET(EFIE2D_SRC ${EFIE2D_SRC_MESH} ${EFIE2D_SRC_MAT} ${EFIE2D_SRC_SOLVER} ${EFIE2D_SRC_KERNEL} ${EFIE2D_SRC_AI_KERNEL})
SET(EFIE2D_SRC ${EFIE2D_SRC_JSON_READER} ${EFIE2D_SRC_MAT} ${EFIE2D_SRC_OBJ} ${EFIE2D_SRC_MESH} ${EFIE2D_SRC_GEO} ${EFIE2D_SRC_MODEL} ${EFIE2D_SRC_EXC})

# Set folder for the Armadillo and Bessel/hankel implementation
SET(Armadillo "D:/CODE/Armadillo/armadillo-8.500.0")
SET(Bessel "D:/CODE/ComplexBesselLib/complex_bessel-release-0.6")
# Set the JSON template lib
SET(JSON_LIB "D:/CODE/json-develop")

# Define the include.
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/google_test/include)
# Include all the EFIE2D /src
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/../src)
# Include armadillo src
INCLUDE_DIRECTORIES(${Armadillo}/include)
# Include Bessel src
INCLUDE_DIRECTORIES(${Bessel}/include)
# Include the JSON lib
INCLUDE_DIRECTORIES(${JSON_LIB}/include ${JSON_LIB}/single_include)

# Link to the Google Test Library.
LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/google_test/lib)
# Link with the Armadillo library
LINK_DIRECTORIES(${Armadillo}/lib_win64)
# Link with the Bessel library
LINK_DIRECTORIES(${Bessel}/lib_win64)

# Add test executable target
ADD_EXECUTABLE(test_efie2d ${CMAKE_SOURCE_DIR}/test.cpp ${EFIE2D_SRC})

# Add the library to the main
TARGET_LINK_LIBRARIES(test_efie2d gtest blas_win64_MT lapack_win64_MT complex_bessel)
