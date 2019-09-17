#!/bin/bash

if [ ! -x "/source/usr/bin/wtex" ]; then
    cmake -S /source -B ~/build -GNinja -Dwt_DIR=$wt_DIR -DCMAKE_INSTALL_PREFIX=$INSTALL_DIR
    cmake --build ~/build --target install
fi 

export LD_LIBRARY_PATH=/usr-wt/lib
#echo "URL: http://127.0.0.1:50080"
/source/usr/bin/wtex --approot  /source/approot --docroot /source/docroot --resources-dir=/usr-wt/share/Wt/resources --http-listen 0.0.0.0:50080 
