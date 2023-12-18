if [ "$3" = "b" ]; then
    cp -R -u -p "$1/day_$2""a.c" "$1/day_$2$3.c"
fi
code "$1/day_$2$3.c"
code "utl.h"
code "$1/input/day_""$2""_example_input.txt"
code "$1/input/day_""$2""_input.txt"
