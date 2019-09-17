#!/bin/bash

if [ ! -x "/sdk/qtcreator/bin/qtcreator" ]; then
    cd /tmp
    wget http://download.qt.io/official_releases/qtcreator/4.10/4.10.0/qt-creator-opensource-linux-x86_64-4.10.0.run
    chmod 555 qt-creator-opensource-linux-x86_64-4.10.0.run
    /tmp/qt-creator-opensource-linux-x86_64-4.10.0.run --script /sdk/qt-creator-installer-noninteractive.qs
    rm -f /tmp/qt-creator-opensource-linux-x86_64-4.10.0.run
fi

#cmake -S/source -B/build/default "-GCodeLite - Ninja" -Dwt_DIR=/usr-wt/lib/cmake/wt

if [ ! -f /source/CMakeLists.txt.user ]; then
    cp /sdk/CMakeLists.txt.save /source/CMakeLists.txt.user
fi

tmux -L wt-sdk-ide new-session -n wt-sdk /sdk/qtcreator/bin/qtcreator /source/CMakeLists.txt || /bin/bash
