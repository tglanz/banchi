#!/bin/bash

commands=()

configuration=Release

while [[ $# -gt 0 ]]
do
    key=$1
    case $key in
        --configuration|-c)
            configuration=$2
            shift
            shift
            ;;
        *)
            commands+=($1)
            shift
            ;;
    esac
done

top_bin_dir=bin
bin_dir=$top_bin_dir/$configuration
build_dir=build
executable=banchi.exe
mkdir -p $bin_dir

printf "\nVariables\n"
printf "%-20s: %s\n" " - bin" $top_bin_dir
printf "%-20s: %s\n" " - configuration" $configuration
printf "%-20s: %s\n" " - executable" $executable
printf "%-20s: %s\n" " - build" $build_dir

for command in ${commands[@]}
do
    echo ""
    echo "running command: $command"

    case $command in
        run)
            cd $bin_dir
            ./$executable &
            cd -
            ;;
        clean)
            target=$top_bin_dir
            echo " - removing $target"
            rm -rf $target
            
            target=$build_dir
            echo " - removing $target"
            rm -rf $target
            ;;
        gen)
            cmake -B$build_dir
            ;;
        build)
            cmake --build build --clean-first --config $configuration
            ;;
        copy)
            from=external/bsf/bin/Data
            to=$bin_dir/Data
            echo "copying $from -> $to"
            cp -r $from $to 2>/dev/null

            from=external/bsf/bin/$configuration/*
            to=$bin_dir
            echo "copying $from -> $to"
            cp -r $from $to 2>/dev/null
            ;;
        *)
            echo "unknown command: $command"
            ;;
    esac
done