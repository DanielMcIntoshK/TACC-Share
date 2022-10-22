#!/bin/bash
#Daniel McIntosh should startup all my transition searches

for file in * ; do 
	if [ -d $file ] ; then
		cd $file
		sbatch RunScript
		cd ..  
	fi
done

