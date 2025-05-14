cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(StHbtMaker)

list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

find_package(ROOT REQUIRED COMPONENTS MathCore RIO Hist Tree Net MathMore EG)
include(${ROOT_USE_FILE})
add_definitions(${ROOT_CXX_FLAGS})

# add_subdirectory(StRoot)
add_subdirectory(StHbtMakerUser)
add_subdirectory(StHbtMaker)
add_subdirectory(StFemtoEvent)
add_subdirectory(StPicoEvent)
add_subdirectory(McDst)
# add_subdirectory(macro)
add_definitions(-D_VANILLA_ROOT_)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall")
set(PROJECT_NAME STHBTMAKER)

set(STHBTMAKER_INCLUDE_DIRECTORIES
  "${CMAKE_CURRENT_SOURCE_DIR}"
  "${CMAKE_CURRENT_SOURCE_DIR}/StHbtMakerUser"
  "${CMAKE_CURRENT_SOURCE_DIR}/StHbtMaker"
  "${CMAKE_CURRENT_SOURCE_DIR}/StFemtoEvent"
  "${CMAKE_CURRENT_SOURCE_DIR}/StPicoEvent"
  "${CMAKE_CURRENT_SOURCE_DIR}/McDst"
  ${ROOT_INLCUDE_DIRS}
)

include_directories(${STHBTMAKER_INCLUDE_DIRECTORIES})

set(STHBTMAKER_INCLUDE_LIBRARIES
  StHbtMakerUser
  StHbtMaker
  StFemtoDst
  StPicoDst
  McDst
  ${ROOT_LIBRARIES}
)

add_executable(hbt_auau_simu "${CMAKE_CURRENT_SOURCE_DIR}/../hbt_auau_simu.cxx")
target_link_libraries(hbt_auau_simu ${STHBTMAKER_INCLUDE_LIBRARIES})