#!/bin/bash

#
# Function that describes how to use this script
#
usage() {
  echo "Usage: $0 action"
  echo "  List of actions:"
  echo "    compile       runs compilation over a set of programs stored in subdirectories"
  echo "    clean         removes compiled libraries, object files and executable files"
  echo "    help          calls this help"
}

#
# Function that compiles project. It assumes very trivial
# (but hardcoded) configuration of directories. One first needs to set PROJDIR
# variable and the please subdirectories as follows
#
# project/
#         StHbtMaker     - main machinery for femtoscopic analysis
#         StHbtMakerUser - user defined cuts, monitors, analyses, etc.
#                          NOTE: libraries with data external data formats should
#                                be compiled first and added to the Makefile
#         McDst          - Monte Carlo data format (or any other format description)
#         macro          - directory that stores configuration (running) sripts for
#                          femtoscopic analysis. Can be compiled for running
#                          in a standalone mode.
#
projectCompilation() {

  # Path to the project directory
  PROJDIR=$1
  echo "Project directory: ${PROJDIR}"

  echo -e "\e[1;31mStart project compilation... \e[0m"

  # Compile StHbtMaker
  echo -e "\e[1;35mStart StHbtMaker compilation ... \e[0m"
  cd ${PROJDIR}/StHbtMaker
  make -j4
  echo -e "\e[1;35mStHbtMaker has been compiled \e[0m"

  # Compile McDst
  echo -e "\e[1;35mStart McDst compilation ... \e[0m"
  cd ${PROJDIR}/McDst
  make -j4
  echo -e "\e[1;35mMcDst has been compiled \e[0m"

  # Compile StPicoDst
  echo -e "\e[1;35mStart StPicoDst compilation ... \e[0m"
  cd ${PROJDIR}/StPicoEvent
  make -j4
  echo -e "\e[1;35mStPicoDst has been compiled \e[0m"

  # Compile StPicoDst
  echo -e "\e[1;35mStart StFemtoDst compilation ... \e[0m"
  cd ${PROJDIR}/StFemtoEvent
  make -j4
  echo -e "\e[1;35mStFemtoDst has been compiled \e[0m"

  # Compile StHbtMakerUser
  echo -e "\e[1;35mStart StHbtMakerUser compilation ... \e[0m"
  cd ${PROJDIR}/StHbtMakerUser
  make -j4
  echo -e "\e[1;35mStHbtMakerUser has been compiled \e[0m"

  # Compile macroses in macro/  to executable files
  if [ -d "${PROJDIR}/macro" ]; then
  echo -e "\e[1;35mStart macro compilation \e[0m"
  cd ${PROJDIR}/macro
  make
  echo -e "\e[1;35mMacroses have been compiled \e[0m"
  else
    echo -e "\e[1;33mNo macro/ directory — skipping macro compilation\e[0m"
  fi



  # Now lets check if libs subdirectory exists.
  cd ${PROJDIR}
  # Check if libs/ subdirectory does not exist
  if [ ! -d "libs" ]; then
    # Create libs/ subdirectory
    mkdir libs
  fi

  # Switching directory
  cd ${PROJDIR}/libs

  # Now lets put (link) all created shared libraris into the libs/ directory
  echo -e "\e[1;31mLinking libraries to the libs/ directory \e[0m"

  if [ ! -L "libStHbtMaker.so" ]; then
    echo "ln -s ${PROJDIR}/StHbtMaker/libStHbtMaker.so ."
    ln -s ${PROJDIR}/StHbtMaker/libStHbtMaker.so .
    if [ -f "../StHbtMaker/StHbtMaker_Dict_rdict.pcm" ]; then
      echo "ln -s ${PROJDIR}/StHbtMaker/StHbtMaker_Dict_rdict.pcm ."
      ln -s ${PROJDIR}/StHbtMaker/StHbtMaker_Dict_rdict.pcm .
    fi
  fi

  if [ ! -L "libMcDst.so" ]; then
    echo "ln -s ${PROJDIR}/McDst/libMcDst.so ."
    ln -s ${PROJDIR}/McDst/libMcDst.so .
    if [ -f "../McDst/McDst_Dict_rdict.pcm" ]; then
      echo "ln -s ${PROJDIR}/McDst/McDst_Dict_rdict.pcm ."
      ln -s ${PROJDIR}/McDst/McDst_Dict_rdict.pcm .
    fi
  fi

  if [ ! -L "libStPicoDst.so" ]; then
    echo "ln -s ${PROJDIR}/StPicoEvent/libStPicoDst.so ."
    ln -s ${PROJDIR}/StPicoEvent/libStPicoDst.so .
    if [ -f "../StPicoEvent/StPicoDst_Dict_rdict.pcm" ]; then
      echo "ln -s ${PROJDIR}/StPicoEvent/StPicoDst_Dict_rdict.pcm ."
      ln -s ${PROJDIR}/StPicoEvent/StPicoDst_Dict_rdict.pcm .
    fi
  fi

  if [ ! -L "libStFemtoDst.so" ]; then
      echo "ln -s ${PROJDIR}/StFemtoEvent/libStFemtoDst.so ."
      ln -s ${PROJDIR}/StFemtoEvent/libStFemtoDst.so .
      if [ -f "../StFemtoEvent/StFemtoDst_Dict_rdict.pcm" ]; then
	  echo "ln -s ${PROJDIR}/StFemtoEvent/StFemtoDst_Dict_rdict.pcm ."
	  ln -s ${PROJDIR}/StFemtoEvent/StFemtoDst_Dict_rdict.pcm .
      fi
  fi

  if [ ! -L "libStHbtMakerUser.so" ]; then
    echo "ln -s ${PROJDIR}/StHbtMakerUser/libStHbtMakerUser.so ."
    ln -s ${PROJDIR}/StHbtMakerUser/libStHbtMakerUser.so .
    if [ -f "../StHbtMakerUser/StHbtMakerUser_Dict_rdict.pcm" ]; then
      echo "ln -s ${PROJDIR}/StHbtMakerUser/StHbtMakerUser_Dict_rdict.pcm ."
      ln -s ${PROJDIR}/StHbtMakerUser/StHbtMakerUser_Dict_rdict.pcm .
    fi
  fi

  echo -e "\e[1;31mLibraries have been linked \e[0m"

  # Check if file that sets enviroment does not exist. If not, create it
  if [ ! -e "sthbtmaker_environment.sh" ]; then

    cat > sthbtmaker_environment.sh << EOF
#!/bin/bash
filnam=\${BASH_SOURCE}
absnam=\`readlink -f \${filnam}\`
pather=\`dirname \${absnam}\`
export STHBTMAKER=\${pather}
export PATH=\${STHBTMAKER}':'\${PATH}
export LD_LIBRARY_PATH=\${STHBTMAKER}':'\${LD_LIBRARY_PATH}
echo STHBTMAKER=\${STHBTMAKER}
EOF

    ls sthbtmaker_environment.sh | echo "sthbtmaker_environment.sh has been created"
  fi
}


#
# Function that removes compiled libraries, object files and executable files
#
projectCleanup() {

  # Path to the directory where the project is stored
  PROJDIR=$1
  echo "Project directory: ${PROJDIR}"

  echo -e "\e[1;31mStart project cleanup ... \e[0m"

  if [ -d "libs" ]; then
    echo -e "\e[1;35mCleaning libs/ ... \e[0m"
    cd ${PROJDIR}/libs
    rm lib*
    rm *.pcm
    cd ${PROJDIR}
    rm -rf libs
    echo -e "\e[1;35mLibraries have been removed \e[0m"
  fi

  if [ -d "StHbtMaker" ]; then
    echo -e "\e[1;35mCleaning StHbtMaker ... \e[0m"
    cd ${PROJDIR}/StHbtMaker
    make distclean
    echo -e "\e[1;35mStHbtMaker has been cleaned \e[0m"
    cd ${PROJDIR}
  fi

  if [ -d "StHbtMakerUser" ]; then
    echo -e "\e[1;35mCleaning StHbtMakerUser ... \e[0m"
    cd ${PROJDIR}/StHbtMakerUser
    make distclean
    echo -e "\e[1;35mStHbtMakerUser has been cleaned \e[0m"
    cd ${PROJDIR}
  fi

  if [ -d "McDst" ]; then
    echo -e "\e[1;35mCleaning McDst ... \e[0m"
    cd ${PROJDIR}/McDst
    make distclean
    echo -e "\e[1;35mMcDt has been cleaned \e[0m"
    cd ${PROJDIR}
  fi

  if [ -d "StPicoEvent" ]; then
    echo -e "\e[1;35mCleaning StPicoEvent ... \e[0m"
    cd ${PROJDIR}/StPicoEvent
    make distclean
    echo -e "\e[1;35mStPicoEvent has been cleaned \e[0m"
    cd ${PROJDIR}
  fi

  if [ -d "StFemtoEvent" ]; then
    echo -e "\e[1;35mCleaning StFemtoEvent ... \e[0m"
    cd ${PROJDIR}/StFemtoEvent
    make distclean
    echo -e "\e[1;35mStFemtoEvent has been cleaned \e[0m"
    cd ${PROJDIR}
  fi

  if [ -d "macro" ]; then
    echo -e "\e[1;35mCleaning macro ... \e[0m"
    cd ${PROJDIR}/macro
    make distclean
    echo -e "\e[1;35mMacro has been cleaned \e[0m"
    cd ${PROJDIR}
  fi

  echo -e "\e[1;31mProject has been cleaned \e[0m"
}

#################################
#                               #
# ENTRANCE POINT OF THE PROGRAM #
#                               #
#################################

# Project directory. One needs to setup the correct path to the project
#PROJDIR=/home/nigmatkulov/work/star/soft/project
PROJDIR=$PWD

# Read command line parameters and choose appropriate action
# Only one action can be chosen at a time
if [ $# -ne 1 ]; then
    usage
    exit 1
fi

# Read command argument from the command line
arg="$1"
# Move ${command} to lowercase (using bash)
command=${arg,,}

# Move ${command} to lowercase (using AWK)
#echo "$1" | awk '{print tolower($0)}'

if [[ "$command" == "compile" ]]; then
  projectCompilation ${PROJDIR}
elif [[ "$command" == "clean" ]]; then
  projectCleanup ${PROJDIR}
else
  echo "Unknown action"
  usage
  exit 1
fi
