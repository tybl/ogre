#!/bin/bash
cmake -S utils/dependencies -B build_deps
cmake --build build_deps
cmake -S . -B build_ogre -DCMAKE_PREFIX_PATH=build_deps
cmake --build build_ogre
