AC_INIT([project], [1.1], [])

dnl Library names (subst down below)
dnl 'lib' prefix will be added later as we need to use these
dnl variables with the linker option -l
STHBTMAKER=StHbtMaker
STPICOEVENT=StPicoEvent
STHBTMAKERUSER=StHbtMakerUser

dnl Debug option
AC_ARG_ENABLE(debug,
              AS_HELP_STRING([--enable-debug],[enable debug information, defult: no]),
              [case "${enableval}" in
               yes) debug=true  ;;
               no)  debug=false ;;
               *)   AC_MSG_ERROR([bad value ${enablevalue} for --enable-debug]) ;;
             esac], [debug=false])

dnl Compile macros as well as libraries
AC_ARG_ENABLE(macro,
              AS_HELP_STRING([--enable-macro],[enable macro, defult: no]),
              [case "${enableval}" in
               yes) macros=true  ;;
               no)  macros=false ;;
               *)   AC_MSG_ERROR([bad value ${enablevalue} for --enable-macro]) ;;
             esac], [macros=false])

dnl native build (do not use STAR software stuff)
AC_ARG_ENABLE(native,
              AS_HELP_STRING([--enable-native],[enable native build (w/o STAR software), defult: yes]),
              [case "${enableval}" in
               yes) native=true ;;
               no)  native=false ;;
               *)   AC_MSG_ERROR([bad value ${enablevalue} for --enable-native]) ;;
             esac], [native=true])

dnl McDst options
AC_ARG_ENABLE(mcdst,
              AS_HELP_STRING([--enable-mcdst],[enable McDst reader support, defult: no]),
              [case "${enableval}" in
               yes) mcdst=true  ;;
               no)  mcdst=false ;;
               *)   AC_MSG_ERROR([bad value ${enablevalue} for --enable-mcdst]) ;;
             esac], [mcdst=false])

AC_ARG_WITH(mcdst, AS_HELP_STRING([--with-mcdst=ARG], [path to the McDst headers and shared library (libMcDst.so), default: no]),
            [mcdst_path=; [ test "x${withval-}" == "xno"] || mcdst_path="${withval-}"], [mcdst_path=])

dnl with StFemtoEvent option
AC_ARG_ENABLE(femtoevent,
              AS_HELP_STRING([--enable-femtoevent],[enable StFemtoEvent reader support, defult: no]),
              [case "${enableval}" in
               yes) femtoevent=true  ;;
               no)  femtoevent=false ;;
               *)   AC_MSG_ERROR([bad value ${enablevalue} for --enable-femtoevent]) ;;
             esac], [femtoevent=false])

AC_ARG_WITH(femtoevent, AS_HELP_STRING([--with-femtoevent=ARG], [path to the StFmetoEvent headers and shared library (libStFemtoDst.so), default: no]),
            [femtoevent_path=; [ test "x${withval-}" == "xno"] || femtoevent_path="${withval-}"], [femtoevent_path=])

dnl
dnl TODO: add dependences checking
dnl

dnl Set default CXXFLAGS in the case if it is _not_ set yet
if [ test -z "${CXXFLAGS-}" ]; then
  if [ test "x$debug" == "xtrue" ]; then
    CXXFLAGS="-g -O0"
  else
    CXXFLAGS="-O2"
  fi
  dnl Define flags. -D_VANILLA_ROOT_ is needed to avoid StMessMgr confusion
  CXXFLAGS="$CXXFLAGS $(root-config --cflags) -fPIC  -W -Woverloaded-virtual -Wno-deprecated-declarations -Wall -pipe -I. -I.. -std=c++11 -D_VANILLA_ROOT_"
fi

dnl Set FCFLAGS if it is _not_ set yet
if [ test -z "${FCFLAGS-}" ]; then
  if [ test "x$debug" == "xtrue" ]; then
    FCFLAGS="-g -O0"
  else
    FCFLAGS="-O2"
  fi
  FCFLAGS="$FCFLAGS -fPIC -pipe $(root-config --cflags)"
fi

dnl Set LDFLAGS if it is _not_ set yet
if [ test -z "${LDFLAGS-}" ]; then
  LDFLAGS="$(root-config --libs --ldflags) -lEG -lgfortran"
fi

dnl Additional LDFLAGS for StHbtMakerUser and macros
LDFLAGS_STHBTMAKERUSER="-L../libs -l$STHBTMAKER -l$STPICOEVENT"
if [ test "x$macros" == "xtrue" ]; then
   if [ test "x$femtoevent" == "xfalse" -o "x$mcdst" == "xfalse" ]; then
      AC_MSG_ERROR("Can't build macros without StFemtoEvent and McDst", 1)
   fi
   if [ test -z "$femtoevent_path" -o -z "$mcdst_path" ]; then
      LDFLAGS_MACROS="-L../libs -l$STHBTMAKERUSER -l$STHBTMAKER -l$STPICOEVENT -lStFemtoDst -lMcDst"
   else
      LDFLAGS_MACROS="-L../libs -l$STHBTMAKERUSER -l$STHBTMAKER -l$STPICOEVENT -L$femtoevent_path -lStFemtoDst -L $mcdst_path -lMcDst"
   fi
fi


dnl add -D__ROOT__ in the case of the native build
if [ test "x$native" == "x$true" ]; then
    CXXFLAGS="$CXXFLAGS -D__ROOT__"
fi

AC_PROG_CXX
AC_PROG_FC

dnl Configure Makefile.in
AC_CONFIG_FILES([Makefile StHbtMaker/autobuild.mk StPicoEvent/autobuild.mk StHbtMakerUser/autobuild.mk])
[ test "x$macros" == "xfalse" ] || AC_CONFIG_FILES([macro/autobuild.mk])

dnl Setup StFemtoEvent and StPicoEvent in StHbtMakerUser
AC_SUBST(femtoevent_path, "$femtoevent_path")
STHBTMAKERUSER_EXCLUDE=
if [ test "x$femtoevent" == "xfalse" ]; then
   STHBTMAKERUSER_EXCLUDE="${STHBTMAKERUSER_EXCLUDE-} StHbtFemtoDstReader.cxx"
else
   if [ test -z "$femtoevent_path" ]; then
      LDFLAGS_STHBTMAKERUSER="${LDFLAGS_STHBTMAKERUSER} -lStFemtoDst"
   else
      CXXFLAGS_STHBTMAKERUSER="-I${femtoevent_path}/.."
      LDFLAGS_STHBTMAKERUSER="${LDFLAGS_STHBTMAKERUSER} -L$femtoevent_path -lStFemtoDst"
   fi
fi
if [ test "x$mcdst" == "xfalse" ]; then
   STHBTMAKERUSER_EXCLUDE="${STHBTMAKERUSER_EXCLUDE-} StHbtMcDstReader.cxx"
else
   if [ test -z "$mcdst_path" ]; then
      LDFLAGS_STHBTMAKERUSER="${LDFLAGS_STHBTMAKERUSER} -lMcDst"
   else
      LDFLAGS_STHBTMAKERUSER="${LDFLAGS_STHBTMAKERUSER} -L$mcdst_path -lMcDst"
      CXXFLAGS_STHBTMAKERUSER="${CXXFLAGS_STHBTMAKERUSER-} -I${mcdst_path}/.."
   fi
fi

dnl Substitutions for Makefiles
AC_SUBST(STHBTMAKERUSER_EXCLUDE, "$STHBTMAKERUSER_EXCLUDE")
AC_SUBST(STHBTMAKER, "lib${STHBTMAKER}.so")
AC_SUBST(STPICOEVENT, "lib${STPICOEVENT}.so")
AC_SUBST(STHBTMAKERUSER, "lib${STHBTMAKERUSER}.so")
AC_SUBST(LDFLAGS_STHBTMAKERUSER, "$LDFLAGS_STHBTMAKERUSER")
AC_SUBST(CXXFLAGS_STHBTMAKERUSER, "${CXXFLAGS_STHBTMAKERUSER-}")
AC_SUBST(BUILD_MACROS, "$macros")
AC_SUBST(LDFLAGS_MACROS, "$LDFLAGS_MACROS")

AC_OUTPUT
