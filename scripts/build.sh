#!/usr/bin/env bash

set -e 

project_root="$(dirname "$(dirname "$(realpath "$0")")")"
cd $project_root
extra_build_args=$*

./.github/scripts/build-linux --target linux-x86_64 $extra_build_args

ln -s build_x86_64/compile_commands.json . || {
    echo "Keeping current compile_commands.json, run 'ln -s build_x86_64/compile_commands.json .' to create a symlink."
}
