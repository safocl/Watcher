#! /bin/sh


for f in $(find . -name '*.cpp' -or -name '*.hpp')
do
    clang-format -i $f;
done
