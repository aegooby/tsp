
if [ "$#" == 0 ]; then
	BUILD_TARGET="Debug"
else
	BUILD_TARGET="$1"
fi

rm -rf build
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE="$BUILD_TARGET" "${@:1}" -G Xcode ../

