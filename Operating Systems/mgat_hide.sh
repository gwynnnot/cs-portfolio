# TOLENTINO, MARY GWYNETH A.
# 2021-02990
# CMSC 125 B5L

#!/bin/bash

echo "All unhidden files: " ; ls

echo ""
for file in "$@"; do
    if [ ! -e "$file" ]; then
        echo "$file does not exist."
        continue
    fi

    if [ "${file:0:1}" == "." ]; then
        echo "$file is hidden."
        unhide=${file:1}
        mv $file "$unhide"
    else
        mv $file ".${file}"
    fi
done  

echo ""
echo "All files after hiding/unhinding:" ; ls -A
