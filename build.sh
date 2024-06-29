if [ -d "build/" ]
then
  cd build 
else
  echo "creating build folder"
  mkdir build 
  cd build
fi
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
make
echo ""
./LRAM
