basedir=$(cd "$(dirname "$0")" || exit; pwd -P)
if [[ $1 = "-br" || $1 = "-b" ]]; then
  g++ -std=c++11 "$basedir"/main.cpp -o "$basedir"/cmake-build-debug/ACM
fi
if [[ $1 = "-br" || $1 = "-r" || -z $1 ]]; then
  "$basedir"/cmake-build-debug/ACM < "$basedir"/cmake-build-debug/input.txt
fi
