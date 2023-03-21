#!/bin/bash
for file in ./configs/*; do
	filename=$(basename $file)
	shortfile="${filename%.*}"
	mkdir $shortfile
	cp $file $shortfile
	cp RunScriptBase ${shortfile}/RunScript
	echo "g16 < $filename > ${shortfile}.log" >> ${shortfile}/RunScript
	cd $shortfile
	sbatch RunScript
	cd ..
done
