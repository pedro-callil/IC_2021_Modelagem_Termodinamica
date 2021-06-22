#! /usr/bin/env bash

analyze_list () {

	for list in $@; do
		for files in $(cat $list); do
			file=$(echo $files | cut -d ',' -f 1)
			zdan1=$(echo $files | cut -d ',' -f 2)
			zdan2=$(echo $files | cut -d ',' -f 3)
			lines=$(wc -l $file | cut -d ' ' -f 1)
			lines=$((lines-1))
			string=$(./bin/FitWaterActivity \
				-m all -M 200 -f $file -Z $zdan1 $zdan2 \
				| grep model | grep -v Caurie \
				| tr -cd '[0-9]\.\n' \
				| tr '\n' ',' \
				| sed -e 's/,$/\n/g' )
			i=0
			while [[ $i -lt $lines ]]; do
				i=$((i + 1))
				echo $string
			done
		done | datamash mean 1-5 -t ','
	done

}

#analyze_list data/lists/aminoacids.txt \
#	data/lists/mono_carbohydrates.txt

#analyze_list data/lists/mono_carbohydrates.txt \
#	data/lists/ternary_carbohydrates.txt \
#	data/lists/quaternary_carbohydrates.txt

#analyze_list data/lists/multi_caurie.txt

analyze_list data/lists/zdan_carbohydrates.txt
