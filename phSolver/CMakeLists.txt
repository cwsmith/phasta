project(phSolver)
set(CMAKE_Fortran_MODULE_DIRECTORY ${phSolver_BINARY_DIR}/modules)
include_directories(${CMAKE_Fortran_MODULE_DIRECTORY})

set(CASES "/path/to/test/cases/"
  CACHE string
  "path to the test cases")
option(PHASTA_TESTING "enable tests" OFF)

add_subdirectory(common)
option(PHASTA_INCOMPRESSIBLE "Build the incompressible solver" OFF)
option(PHASTA_COMPRESSIBLE "Build the compressible solver" ON)
if(PHASTA_INCOMPRESSIBLE)
add_subdirectory(incompressible)
endif(PHASTA_INCOMPRESSIBLE)
if(PHASTA_COMPRESSIBLE)
add_subdirectory(compressible)
endif(PHASTA_COMPRESSIBLE)

configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/phastaConfig.cmake.in"
  "${CMAKE_BINARY_DIR}/phastaConfig.cmake"
)

