#!/bin/bash

root_path=$(dirname "$(readlink -f "$0")")
echo "You Can Input q For Abort."
read -p "Input Git Commit Info: " commit_info
if [ "$commit_info" != "q" ]; then
    cd "$root_path"
    git status
    git add -A
    git commit -m "$commit_info"
    git push --force
fi
