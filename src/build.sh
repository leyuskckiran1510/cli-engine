compile(){
    gcc -o $1.out $1 -lm `pkg-config --cflags glib-2.0` -ggdb -lglib-2.0

}

debug(){
  compile $1;
  gf2 ./$1.out
}

clean(){
    rm $1.out
}

run(){
    compile $1;
    ./$1.out $@;
    clean $1;
}

case $1 in
  run )run main.c;;
  com)compile main.c;;
  debug)debug main.c;;
  clean)clean main.c;;
esac
