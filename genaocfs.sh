#!/bin/bash
for i in {1..25}
do
	printf -v i "%02d" $i
	if [ -d "./AoC2020_Day$i" ]; then
		echo "Day $i already exists; skipping."
	else
		mkdir AoC2020_Day$i
		cd ./AoC2020_Day$i
		touch main.c
		echo -e "#include <stdio.h>\n\nint main(int argc, const char *argv[])\n{\n  printf(\"Hello World\\\n\");\n  return 0;\n}" >> main.c
		touch input.txt
		touch testinput.txt
		cd ..
	fi
done
