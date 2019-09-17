#!/bin/bash

git clone --branch 4.1.1 --single-branch --depth 1 https://github.com/emweb/wt.git $SRC_DIR
cmake -S $SRC_DIR -B ~/build -GNinja -DCMAKE_INSTALL_PREFIX=$wt_DIR -DINSTALL_DOCUMENTATION=ON -DINSTALL_EXAMPLES=ON
cmake --build ~/build --target install
