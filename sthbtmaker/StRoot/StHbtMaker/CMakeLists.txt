# CMakeLists.txt for StFemtoEvent package. It creates a library with dictionary
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(StHbtMaker)

# You need to tell CMake where to find the ROOT installation. This can be done in a number of ways:
#   - ROOT built with classic configure/make use the provided $ROOTSYS/etc/cmake/FindROOT.cmake
#   - ROOT built with CMake. Add in CMAKE_PREFIX_PATH the installation prefix for ROOT
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

#---Locate the ROOT package and defines a number of variables (e.g. ROOT_INCLUDE_DIRS)
find_package(ROOT REQUIRED COMPONENTS MathCore RIO Hist Tree Net EG)

#---Define useful ROOT functions and macros (e.g. ROOT_GENERATE_DICTIONARY)
if(ROOT_CMAKE)
  include(${ROOT_USE_FILE})
endif(ROOT_CMAKE)

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
	"${CMAKE_CURRENT_SOURCE_DIR}/StHbtAnalysis.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/StHbtBaseCorrFctn.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/StHbtBaseCutMonitor.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/StHbtBaseEventReader.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/StHbtBaseModelFreezeOutGenerator.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/StHbtBaseModelWeightGenerator.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/StHbtCutMonitorHandler.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/StHbtEvent.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/StHbtHelix.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/StHbtKink.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/StHbtLikeSignAnalysis.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/StHbtMaker.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/StHbtManager.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/StHbtModelGausLCMSFreezeOutGenerator.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/StHbtModelHiddenInfo.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/StHbtModelManager.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/StHbtModelWeightGeneratorLednicky.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/StHbtMultiTrackCut.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/StHbtPair.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/StHbtParticle.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/StHbtPhysicalHelix.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/StHbtPicoEvent.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/StHbtPicoEventCollectionVectorHideAway.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/StHbtTrack.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/StHbtTriplet.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/StHbtV0.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/StHbtXi.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/TpcLocalTransform.h"
)

set(CXX_FILES
	"${CMAKE_CURRENT_SOURCE_DIR}/StHbtAnalysis.cxx"
	"${CMAKE_CURRENT_SOURCE_DIR}/StHbtBaseCorrFctn.cxx"
	"${CMAKE_CURRENT_SOURCE_DIR}/StHbtBaseCutMonitor.cxx"
	"${CMAKE_CURRENT_SOURCE_DIR}/StHbtBaseEventReader.cxx"
	"${CMAKE_CURRENT_SOURCE_DIR}/StHbtBaseModelFreezeOutGenerator.cxx"
	"${CMAKE_CURRENT_SOURCE_DIR}/StHbtBaseModelWeightGenerator.cxx"
	"${CMAKE_CURRENT_SOURCE_DIR}/StHbtCutMonitorHandler.cxx"
	"${CMAKE_CURRENT_SOURCE_DIR}/StHbtEvent.cxx"
	"${CMAKE_CURRENT_SOURCE_DIR}/StHbtHelix.cxx"
	"${CMAKE_CURRENT_SOURCE_DIR}/StHbtKink.cxx"
	"${CMAKE_CURRENT_SOURCE_DIR}/StHbtLikeSignAnalysis.cxx"
	"${CMAKE_CURRENT_SOURCE_DIR}/StHbtMaker.cxx"
	"${CMAKE_CURRENT_SOURCE_DIR}/StHbtManager.cxx"
	"${CMAKE_CURRENT_SOURCE_DIR}/StHbtModelGausLCMSFreezeOutGenerator.cxx"
	"${CMAKE_CURRENT_SOURCE_DIR}/StHbtModelHiddenInfo.cxx"
	"${CMAKE_CURRENT_SOURCE_DIR}/StHbtModelManager.cxx"
	"${CMAKE_CURRENT_SOURCE_DIR}/StHbtModelWeightGeneratorLednicky.cxx"
	"${CMAKE_CURRENT_SOURCE_DIR}/StHbtMultiTrackCut.cxx"
	"${CMAKE_CURRENT_SOURCE_DIR}/StHbtPair.cxx"
	"${CMAKE_CURRENT_SOURCE_DIR}/StHbtParticle.cxx"
	"${CMAKE_CURRENT_SOURCE_DIR}/StHbtPhysicalHelix.cxx"
	"${CMAKE_CURRENT_SOURCE_DIR}/StHbtPicoEvent.cxx"
	"${CMAKE_CURRENT_SOURCE_DIR}/StHbtPicoEventCollectionVectorHideAway.cxx"
	"${CMAKE_CURRENT_SOURCE_DIR}/StHbtTrack.cxx"
	"${CMAKE_CURRENT_SOURCE_DIR}/StHbtTriplet.cxx"
	"${CMAKE_CURRENT_SOURCE_DIR}/StHbtV0.cxx"
	"${CMAKE_CURRENT_SOURCE_DIR}/StHbtXi.cxx"
	"${CMAKE_CURRENT_SOURCE_DIR}/TpcLocalTransform.cxx"
)

#---Generate dictionary for the project
ROOT_GENERATE_DICTIONARY(G__StHbtMaker
	${HEADER_FILES}
	LINKDEF StHbtMakerLinkDef.h)

enable_language(Fortran)
set(FORTRAN_CODE
	"${CMAKE_CURRENT_SOURCE_DIR}/StHbtFsiTools.F"
	"${CMAKE_CURRENT_SOURCE_DIR}/StHbtFsiWeightLednicky.F"
)

#---Create a shared library with generated dictionary
add_library(StHbtMaker SHARED
	${FORTRAN_CODE}
	${CXX_FILES}
	G__StHbtMaker.cxx)

target_link_libraries(StHbtMaker ${ROOT_LIBRARIES})
