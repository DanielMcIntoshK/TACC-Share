#!/bin/bash
#Daniel McIntosh should startup all my transition searches

for file in * ; do 
	if [ -d $file ] ; then
		dos2unix $file/$file.config
		echo sbatch $file/RunScript  
	fi
done

