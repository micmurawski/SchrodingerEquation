#!/bin/bash
#echo $1
for i in $(eval echo {$1..$2..$3})
do
echo `sed -i '6s/.*/'$i'/' input`
echo `./program input avs$i.dat output`
done

