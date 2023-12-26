#!/bin/bash

RESULT=$(zenity --forms --title="Search files - #3 script" \
--text="Use this program to search files with given parameters" \
--add-entry="1. Name (with extension)" \
--add-entry="2. Directory" \
--add-entry="3. Greater than (file size, bytes)" \
--add-entry="4. Less than (file size, bytes)" \
--add-entry="5. Content")

FILE_NAME=$(echo $RESULT| cut -d '|' -f 1)
DIRECTORY=$(echo $RESULT| cut -d '|' -f 2)
GREATER_THAN=$(echo $RESULT| cut -d '|' -f 3)
LESS_THAN=$(echo $RESULT| cut -d '|' -f 4)
CONTENT=$(echo $RESULT| cut -d '|' -f 5)

echo $FILE_NAME
echo $DIRECTORY
echo $GREATER_THAN
echo $LESS_THAN
echo $CONTENT

echo "Running search"
find -path "$(DIRECTORY_NAME}/$(FILE_NAME)"
