mkdir -p build
cd build
echo "\033[32mBuild Makefile ...\033[0m"
cmake -Wno-dev ..
echo "\033[32mCompile sources ...\033[0m"
rm -f ./build/CommunityGame_Engine
make
if [[ "$?" -eq "0" ]]; then 
	cd ..
	echo "\033[32mStart game engine ...\n\t----\033[0m"
	./build/CommunityGame_Engine $1
else
	echo "\033[31mError failed to build\033[0m"
fi
