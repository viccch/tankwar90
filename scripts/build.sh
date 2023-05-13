# /bin/bash
cd $(dirname $0)

# sudo apt install curl libfreetype-dev libglfw3-dev libglew-dev libglm-dev libstb-dev

rm -rf ../build
mkdir -p ../build
cd ../build

curl -# -O https://www.ambiera.at/downloads/irrKlang-64bit-1.6.0.zip
unzip -o irrKlang-64bit-1.6.0.zip > /dev/null

mkdir -p ../third_party/include/irrklang/
mkdir -p ../third_party/lib/linux/
cp -r irrKlang-64bit-1.6.0/bin/linux-gcc-64/*.so ../third_party/lib/linux/
cp -r irrKlang-64bit-1.6.0/include/* ../third_party/include/irrklang/

cmake ..
cmake --build .
cd ..

