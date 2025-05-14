# CMakeLists.txt for StFemtoEvent package. It creates a library with dictionary
# cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
# project(StPicoDst)

# You need to tell CMake where to find the ROOT installation. This can be done in a number of ways:
#   - ROOT built with classic configure/make use the provided $ROOTSYS/etc/cmake/FindROOT.cmake
#   - ROOT built with CMake. Add in CMAKE_PREFIX_PATH the installation prefix for ROOT
# list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

#---Locate the ROOT package and defines a number of variables (e.g. ROOT_INCLUDE_DIRS)
# find_package(ROOT REQUIRED COMPONENTS MathCore RIO Hist Tree Net)

#---Define useful ROOT functions and macros (e.g. ROOT_GENERATE_DICTIONARY)
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
	"${CMAKE_CURRENT_SOURCE_DIR}/StPicoArrays.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/StPicoBEmcPidTraits.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/StPicoBEmcSmdEHit.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/StPicoBEmcSmdPHit.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/StPicoBTofHit.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/StPicoBTofPidTraits.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/StPicoBTowHit.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/StPicoBbcHit.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/StPicoCommon.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/StPicoDst.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/StPicoDstReader.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/StPicoETofHit.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/StPicoETofPidTraits.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/StPicoEmcTrigger.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/StPicoEpdHit.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/StPicoEvent.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/StPicoFmsHit.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/StPicoHelix.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/StPicoMcTrack.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/StPicoMcVertex.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/StPicoMtdHit.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/StPicoMtdPidTraits.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/StPicoMtdTrigger.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/StPicoPhysicalHelix.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/StPicoTrack.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/StPicoTrackCovMatrix.h"
)

set(CXX_FILES
	"${CMAKE_CURRENT_SOURCE_DIR}/StPicoArrays.cxx"
	"${CMAKE_CURRENT_SOURCE_DIR}/StPicoBEmcPidTraits.cxx"
	"${CMAKE_CURRENT_SOURCE_DIR}/StPicoBEmcSmdEHit.cxx"
	"${CMAKE_CURRENT_SOURCE_DIR}/StPicoBEmcSmdPHit.cxx"
	"${CMAKE_CURRENT_SOURCE_DIR}/StPicoBTofHit.cxx"
	"${CMAKE_CURRENT_SOURCE_DIR}/StPicoBTofPidTraits.cxx"
	"${CMAKE_CURRENT_SOURCE_DIR}/StPicoBTowHit.cxx"
	"${CMAKE_CURRENT_SOURCE_DIR}/StPicoBbcHit.cxx"
	"${CMAKE_CURRENT_SOURCE_DIR}/StPicoCommon.cxx"
	"${CMAKE_CURRENT_SOURCE_DIR}/StPicoDst.cxx"
	"${CMAKE_CURRENT_SOURCE_DIR}/StPicoDstReader.cxx"
	"${CMAKE_CURRENT_SOURCE_DIR}/StPicoETofHit.cxx"
	"${CMAKE_CURRENT_SOURCE_DIR}/StPicoETofPidTraits.cxx"
	"${CMAKE_CURRENT_SOURCE_DIR}/StPicoEmcTrigger.cxx"
	"${CMAKE_CURRENT_SOURCE_DIR}/StPicoEpdHit.cxx"
	"${CMAKE_CURRENT_SOURCE_DIR}/StPicoEvent.cxx"
	"${CMAKE_CURRENT_SOURCE_DIR}/StPicoFmsHit.cxx"
	"${CMAKE_CURRENT_SOURCE_DIR}/StPicoHelix.cxx"
	"${CMAKE_CURRENT_SOURCE_DIR}/StPicoMcTrack.cxx"
	"${CMAKE_CURRENT_SOURCE_DIR}/StPicoMcVertex.cxx"
	"${CMAKE_CURRENT_SOURCE_DIR}/StPicoMtdHit.cxx"
	"${CMAKE_CURRENT_SOURCE_DIR}/StPicoMtdPidTraits.cxx"
	"${CMAKE_CURRENT_SOURCE_DIR}/StPicoMtdTrigger.cxx"
	"${CMAKE_CURRENT_SOURCE_DIR}/StPicoPhysicalHelix.cxx"
	"${CMAKE_CURRENT_SOURCE_DIR}/StPicoTrack.cxx"
	"${CMAKE_CURRENT_SOURCE_DIR}/StPicoTrackCovMatrix.cxx"
)

#---Generate dictionary for the project
ROOT_GENERATE_DICTIONARY(G__StPicoDst
	${HEADER_FILES}
	LINKDEF StPicoDstLinkDef.h)

#---Create a shared library with generated dictionary
add_library(StPicoDst SHARED
	${CXX_FILES}
	G__StPicoDst.cxx)

target_link_libraries(StPicoDst ${ROOT_LIBRARIES})
