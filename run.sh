mkdir -p build
cd build
echo "\033[32mBuild Makefile ...\033[0m"
cmake -Wno-dev ..
echo "\033[32mCompile sources ...\033[0m"
rm -f ./build/CommunityGame_Engine
make
cd ..
echo "\033[32mStart game engine ...\n\t----\033[0m"
if [ -f ./build/CommunityGame_Engine ]; then 
	./build/CommunityGame_Engine
else
	echo "\033[31mError failed to build\033[0m"
fi
