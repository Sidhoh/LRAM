cd build
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
make
echo ""
./LRAM
