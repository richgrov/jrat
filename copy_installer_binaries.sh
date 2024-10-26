if [[ ! $1 ]]; then
  echo "error: specify build directory"
  exit 1
fi

if [[ $(uname) == *"MINGW"* ]]; then
  exe_suffix=".exe"
  lib_suffix=".dll"
fi

mkdir -p installer/res

cp $1/flipinator/flipinator$exe_suffix installer/res/flipinator$exe_suffix
cp $1/convertinator/convertinator$exe_suffix installer/res/convertinator$exe_suffix
cp $1/cropinator/cropinator$exe_suffix installer/res/cropinator$exe_suffix
cp $1/erasinator/erasinator$exe_suffix installer/res/erasinator$exe_suffix
cp $1/resizinator/resizinator$exe_suffix installer/res/resizinator$exe_suffix
cp $1/rotatinator/rotatinator$exe_suffix installer/res/rotatinator$exe_suffix

cp opencv_world490$lib_suffix installer/res/opencv_world490$lib_suffix
