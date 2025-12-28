cd build
cmake ..
make
cd ..
cp build/compile_commands.json .
build/tintr $1
