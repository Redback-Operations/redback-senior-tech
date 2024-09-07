#!/bin/bash

# Function to rename files and folders
rename_files() {
  for file in "$1"/*; do
    if [[ "$file" == *.md ]]; then
      # Rename markdown files to uppercase
      rename 's/ /_/g' 's/[a-z]/\U$&/g' "$file"
    else
      # Rename other files and folders to lowercase
      rename 's/ /_/g' 's/[A-Z]/\L$&/g' "$file"
    fi
  done
}

# Get the directory to process
echo "Enter the directory you want to rename files in:"
read directory

# Check if the directory exists
if [[ ! -d "$directory" ]]; then
  echo "Directory not found."
  exit 1
fi

# Call the rename function
rename_files "$directory"
