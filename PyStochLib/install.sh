#!/bin/bash
#perform installation steps

#set -x

if [ "$PYTHON_HOME" == "" ]; then
  pushd "$(dirname "$0")" > /dev/null
  export PYTHON_HOME=`python -c "import sys; print sys.prefix"`
  popd > /dev/null
fi

make