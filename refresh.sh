basedir=$(cd "$(dirname "$0")" || exit; pwd -P)
cp "$basedir/template/main" "$basedir/main.cpp"