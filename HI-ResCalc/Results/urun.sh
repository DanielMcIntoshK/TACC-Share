#!/bin/bash
for file in ../configs/*; do
	filename=$(basename $file)
	shortfile="${filename%.*}"
	mkdir $shortfile
	cd $shortfile
	rm error.* output.* checkpoint.chk
	cd ..
done
