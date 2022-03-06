#!/bin/bash

for i in {1..100}
do
	echo "Working $i.."
	echo -n "$i," >> virtual.csv
	Optimized/src/exp-virtual
done
