#!/bin/bash
if [ -d "./AoC2020_Day$1" ]; then
	echo -e "\e[31mError:\e[0m Directory already created for this day. Remove and recreate it, or choose a different day."
else
	mkdir ./AoC2020_Day$1
	cd ./AoC2020_Day$1
	touch ./input.txt
	touch ./testinput.txt
fi
