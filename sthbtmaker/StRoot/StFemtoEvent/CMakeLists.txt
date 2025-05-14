# # CMakeLists.txt for StFemtoEvent package. It creates a library with dictionary
# cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
# project(StFemtoDst)

# # You need to tell CMake where to find the ROOT installation. This can be done in a number of ways:
# #   - ROOT built with classic configure/make use the provided $ROOTSYS/etc/cmake/FindROOT.cmake
# #   - ROOT built with CMake. Add in CMAKE_PREFIX_PATH the installation prefix for ROOT
# list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

# #---Locate the ROOT package and defines a number of variables (e.g. ROOT_INCLUDE_DIRS)
# find_package(ROOT REQUIRED COMPONENTS MathCore RIO Hist Tree Net)

# #---Define useful ROOT functions and macros (e.g. ROOT_GENERATE_DICTIONARY)
# if(ROOT_CMAKE)
#   include(${ROOT_USE_FILE})
# endif(ROOT_CMAKE)

#---Define _VANILLA_ROOT_ variable needed for the project
add_definitions(-D_VANILLA_ROOT_)

set(INCLUDE_DIRECTORIES
  ${CMAKE_SOURCE_DIR}
  ${ROOT_INCLUDE_DIRS}
)

include_directories(${INCLUDE_DIRECTORIES})
add_definitions(${ROOT_CXX_FLAGS})

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS "-O2")

set(HEADER_FILES
	# "${CMAKE_CURRENT_SOURCE_DIR}/PhysicalConstants.h"
	# "${CMAKE_CURRENT_SOURCE_DIR}/StFemtoMessMgr.h"
	# "${CMAKE_CURRENT_SOURCE_DIR}/SystemOfUnits.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/StFemtoArrays.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/StFemtoDst.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/StFemtoDstReader.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/StFemtoEvent.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/StFemtoHelix.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/StFemtoPhysicalHelix.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/StFemtoTrack.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/StFemtoV0.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/StFemtoXi.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/StFemtoKFP.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/StFemtoEpdHit.h"
)

set(CXX_FILES
	"${CMAKE_CURRENT_SOURCE_DIR}/StFemtoArrays.cxx"
	"${CMAKE_CURRENT_SOURCE_DIR}/StFemtoDst.cxx"
	"${CMAKE_CURRENT_SOURCE_DIR}/StFemtoDstReader.cxx"
	"${CMAKE_CURRENT_SOURCE_DIR}/StFemtoEvent.cxx"
	"${CMAKE_CURRENT_SOURCE_DIR}/StFemtoHelix.cxx"
	"${CMAKE_CURRENT_SOURCE_DIR}/StFemtoPhysicalHelix.cxx"
	"${CMAKE_CURRENT_SOURCE_DIR}/StFemtoTrack.cxx"
	"${CMAKE_CURRENT_SOURCE_DIR}/StFemtoV0.cxx"
	"${CMAKE_CURRENT_SOURCE_DIR}/StFemtoXi.cxx"
	"${CMAKE_CURRENT_SOURCE_DIR}/StFemtoKFP.cxx"
	"${CMAKE_CURRENT_SOURCE_DIR}/StFemtoEpdHit.cxx"
)

#---Generate dictionary for the project
ROOT_GENERATE_DICTIONARY(G__StFemtoDst
	${HEADER_FILES}
	LINKDEF StFemtoDstLinkDef.h)

#---Create a shared library with generated dictionary
add_library(StFemtoDst SHARED
	${CXX_FILES}
	G__StFemtoDst.cxx)

target_link_libraries(StFemtoDst ${ROOT_LIBRARIES})
