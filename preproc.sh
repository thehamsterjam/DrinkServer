#!/bin/bash

for filename in src/*.html; do
    echo 'R"(' > "$filename"".inc"
    cat $filename >> "$filename"".inc";
    echo ')";' >> "$filename"".inc"
done
