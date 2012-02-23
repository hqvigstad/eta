#!/bin/bash

build_dir=$1
task_dir=../tasks/
task_src=$(ls $task_dir/*.cxx $task_dir/*.h)


mkdir $build_dir
for file in $task_src
do
    cp $file $build_dir
done
cp runLocal.C $build_dir
cp -r tags $build_dir

