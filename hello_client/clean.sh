#!/bin/bash
root_path=$(dirname "$(readlink -f "$0")")
project_name=$(basename $root_path)
build_path="$root_path/build/linux"
bin_path="$root_path/$project_name"
if [ -d "$build_path" ]; then
    rm -rf "$build_path"
fi
if [ -e "$bin_path" ]; then
    rm -rf "$bin_path"
fi
