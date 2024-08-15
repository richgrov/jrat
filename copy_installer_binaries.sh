if [[ $1 -eq 0 ]] then
  echo "error: specify build directory"
  exit 1
fi

if [[ $(uname) == *"MINGW"* ]] then
  exe_suffix=".exe"
  lib_suffix=".dll"
fi

mkdir -p installer/res

cp $1/convertinator/convertinator$suffix installer/res/convertinator$suffix
cp opencv_world490$lib_suffix installer/res/opencv_world490$lib_suffix
