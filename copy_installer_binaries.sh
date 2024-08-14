if [[ $(uname) == *"MINGW"* ]] then
  exe_suffix=".exe"
  lib_suffix=".dll"
fi

cp $1/convertinator/convertinator$suffix installer/res/convertinator$suffix
cp opencv_world490$lib_suffix installer/res/opencv_world490$lib_suffix
