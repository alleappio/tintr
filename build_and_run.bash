cd build
cmake ..
make
cd ..
cp build/compile_commands.json .
build/colorscheme_util $1
