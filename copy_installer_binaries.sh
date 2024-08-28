if [[ ! $1 ]]; then
  echo "error: specify build directory"
  exit 1
fi

if [[ $(uname) == *"MINGW"* ]]; then
  exe_suffix=".exe"
  lib_suffix=".dll"
fi

mkdir -p installer/res

cp $1/flipinator/flipinator$suffix installer/res/flipinator$suffix
cp $1/convertinator/convertinator$suffix installer/res/convertinator$suffix
cp $1/cropinator/cropinator$suffix installer/res/cropinator$suffix
cp $1/erasinator/erasinator$suffix installer/res/erasinator$suffix
cp $1/resizinator/resizinator$suffix installer/res/resizinator$suffix
cp $1/rotatinator/rotatinator$suffix installer/res/rotatinator$suffix

cp opencv_world490$lib_suffix installer/res/opencv_world490$lib_suffix
