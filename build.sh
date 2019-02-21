echo " building is in progress"
sudo rm -rf build
mkdir build
cd build
cmake -DWITH_DOC=ON -DCLANG_SANITIZER=address ../