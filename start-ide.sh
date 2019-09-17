#!/bin/bash

if [ ! `which docker-compose` ]; then
  echo "docker-compose is not installed. Please install docker-compose via: sudo apt-get install docker-compose"
  exit 1;
fi

if [ ! -d "build/usr-wt" ]; then
    mkdir build/usr-wt;
fi

if [ ! -d "build/src-wt" ]; then
    mkdir build/src-wt;
fi

if [ ! -d "build/ide-build" ]; then
    mkdir build/ide-build;
fi

export USER_ID=$(id -u ${USER})
export GROUP_ID=$(id -g ${USER})

if [ ! -f "build/usr-wt/lib/libwt.so" ]; then
  docker-compose -f build/docker-compose.yml run --rm build-wt
fi

docker-compose -f build/docker-compose.yml run --rm run-dev-ide
