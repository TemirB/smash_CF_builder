#!/bin/bash
filnam=${BASH_SOURCE}
absnam=`readlink -f ${filnam}`
pather=`dirname ${absnam}`
export STHBTMAKER=${pather}
export PATH=${STHBTMAKER}':'${PATH}
export LD_LIBRARY_PATH=${STHBTMAKER}':'${LD_LIBRARY_PATH}
echo STHBTMAKER=${STHBTMAKER}
