#!/bin/sh

if ! [ -x "$(command -v cmake)" ]; then
    echo "You don't have cmake installed; use the Makefile instead."
    exit 1
fi

if [ ! -d build ]; then
  cmake -S. -Bbuild -G "Unix Makefiles" > /dev/null
fi

if [ -z "$1" ]; then
  echo "Usage:"
  echo "  $0 <command> [<container>]"
  echo ""
  echo "Use $0 help for more information."
fi

if [ "$1" = "help" ]; then
  echo "Available options:"
  echo "        build"
  echo "        run <container>"
  echo "        leaks <container>"
fi

if [ "$1" = "build" ]; then
  cmake --build build
fi

if [ "$1" = "run" ]; then
  if [ -n "$2" ]; then
    build/"$2" 2> /dev/null || echo "Failed running $2; try running $0 build if you haven't done so."
  else
    echo "Usage: $0 run <container>"
  fi
fi

if [ "$1" = "leaks" ]; then
  if [ -n "$2" ]; then
    if [ -f "build/$2" ]; then
      leaks --atExit -- build/$2 2> /dev/null
    else
      echo "Please specify an existing container."
    fi
  else
    echo "Usage: $0 leaks <container>"
  fi
fi
