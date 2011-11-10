#!/bin/bash

build_dir=$1
task_dir=../tasks/
task_src=$(ls $task_dir/*.cxx $task_dir/*.h)


mkdir $build_dir
for file in $task_src
do
    cp $file $build_dir
done
cp ConfigureCuts.C $build_dir
cp CreateAlienHandler.C $build_dir
cp runGrid.C $build_dir

