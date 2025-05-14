#!/bin/bash

# assuming that this macro is sitting at its original location,
# its path can be used to set the StHbtMaker environment

filnam=$BASH_SOURCE            # filename of this (sourced) macro
absnam=`readlink -f $filnam`   # absolute filename
pather=`dirname $absnam`       # path to the config directory
#pather=`dirname $pather`       # path to the top unigen directory

export STHBTMAKER=$pather

export PATH=${STHBTMAKER}':'${PATH}
export LD_LIBRARY_PATH=${STHBTMAKER}':'${LD_LIBRARY_PATH}

echo STHBTMAKER = $STHBTMAKER
