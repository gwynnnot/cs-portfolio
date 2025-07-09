# TOLENTINO, MARY GWYNETH A.
# 2021-02990
# CMSC 125 B5L

#!/bin/bash

src=$1
# echo $src
dest=$2
# echo $dest

# check if file does not exist
if [ ! -e "$src" ]; then
    echo "$src does not exist."
elif [[ -e "$src" && -d "$dest" ]]; then
    mv "$src" "$dest"
    cd "$dest"
else
    echo "File or directory does not exist."
fi
