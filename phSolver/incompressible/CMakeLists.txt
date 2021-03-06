file(GLOB SRC_FILES *.cc *.f *.f90 *.c)
list(REMOVE_ITEM SRC_FILES "main.cc")
add_library(incompressible ${SRC_FILES})

find_package(phastaCommon REQUIRED PATHS ${CMAKE_BINARY_DIR})
set(PHASTAIC_LIBS ${CMAKE_THREAD_LIBS_INIT} ${PHASTA_COMMON_LIBS})
set(PHASTAIC_INCLUDE_DIRS
  ${PHASTAIC_INCLUDE_DIRS}
  ${PHASTA_COMMON_INCLUDE_DIRS}
  ${PHASTA_BINARY_DIR}
)

add_executable(phastaIC.exe main.cc)
include_directories(${PHASTAIC_INCLUDE_DIRS})
set_target_properties(phastaIC.exe PROPERTIES HAS_CXX TRUE)
set_target_properties(incompressible PROPERTIES HAS_CXX TRUE)
set_target_properties(phastaIC.exe PROPERTIES LINKER_LANGUAGE Fortran)
set_target_properties(incompressible PROPERTIES LINKER_LANGUAGE Fortran)
if(CMAKE_Fortran_COMPILER_ID MATCHES XL)
	#force preprocessing of solfar.f
	set_source_files_properties(solfar.f PROPERTIES COMPILE_FLAGS "-qsuffix=cpp=f")
endif(CMAKE_Fortran_COMPILER_ID MATCHES XL)
if(CMAKE_Fortran_COMPILER_ID MATCHES PGI)
	#force preprocessing of solfar.f
	set_source_files_properties(solfar.f PROPERTIES COMPILE_FLAGS "-Mpreprocess")
endif(CMAKE_Fortran_COMPILER_ID MATCHES PGI)
#incompressible reuses a fortran module from common w/o telling cmake
#this is why we specify a module directory in the next cmakelists up
#and we need to serialize incompressible after common
add_dependencies(incompressible common)
find_library(ACUSOLVE_LIB libles)
#ughhh
set(PHASTAIC_LIBS
  ${PHASTA_COMMON_LIBS}
  incompressible
  ${ACUSOLVE_LIB}
  incompressible
  ${PHASTA_COMMON_LIBS}
)
set(PHASTAIC_LIBS ${PHASTAIC_LIBS} phastaIO)
if(PHASTA_BUILD_SHAPEFUNCTION)
  set(PHASTAIC_LIBS ${PHASTAIC_LIBS} shapeFunction)
endif(PHASTA_BUILD_SHAPEFUNCTION)
if(PHASTA_BUILD_PHSHAPE)
  set(PHASTAIC_LIBS ${PHASTAIC_LIBS} phshape)
endif(PHASTA_BUILD_PHSHAPE)
target_link_libraries(phastaIC.exe ${PHASTAIC_LIBS})

configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/phastaICConfig.cmake.in"
  "${CMAKE_BINARY_DIR}/phastaICConfig.cmake"
)

if(PHASTA_TESTING)
  add_subdirectory(test)
endif(PHASTA_TESTING)
