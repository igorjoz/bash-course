#!/bin/bash

userInput=0

fileName=
directoryName=
fileSizeGreaterThan=
fileSizeLessThan=
fileContent=

while [ $userInput != "7" ]; do
    echo "1. File name (with extension): $fileName"
    echo "2. Directory name: $directoryName"
    echo "3. Greater than (file size, bytes): $fileSizeGreaterThan"
    echo "4. Less than (file size, bytes): $fileSizeLessThan"
    echo "5. Content: $fileContent"
    echo "6. Run search: " 
    echo "7. Quit: " 

    read userInput

    clear

    case "$userInput" in
        1|"1.")
            read fileName
            fileNameQuery="-name" "$fileName"
            if [ -z $fileName ]; then
                fileNameQuery=""
            fi
            ;;

        2|"2.")
            read directoryName
            directoryNameQuery="${directoryName}"
            if [ -z $directoryName ]; then
                directoryNameQuery=""
            fi
            ;;

        3|"3.")
            read fileSizeGreaterThan
            fileSizeGreaterThanQuery="-size" "+${fileSizeGreaterThan}c"
            if [ -z $fileSizeGreaterThan ]; then
                fileSizeGreaterThanQuery=""
            fi
            ;;

        4|"4.")
            read fileSizeLessThan
            fileSizeLessThanQuery="-size" "-${fileSizeLessThan}c"
            if [ -z $fileSizeLessThan ]; then
                fileSizeLessThanQuery=""
            fi
            ;;

        5|"5.")
            read fileContent
            fileContentQuery=()
            if [ ! -z "$fileContent" ]; then
                fileContentQuery+=("-exec")
                fileContentQuery+=("grep")
                fileContentQuery+=("-l")
                fileContentQuery+=("$fileContent")
                fileContentQuery+=("{}")
                fileContentQuery+=(";")
            fi
            ;;

        6|"6.")
            findCmd=()

            if [ ! -z "$directoryNameQuery" ]; then
                findCmd+=("$directoryNameQuery")
            fi

            if [ ! -z "$fileNameQuery" ]; then
                findCmd+=("$fileNameQuery")
            fi

            if [ ! -z "$fileSizeGreaterThanQuery" ]; then
                findCmd+=("$fileSizeGreaterThanQuery")
            fi

            if [ ! -z "$fileSizeLessThanQuery" ]; then
                findCmd+=("$fileSizeLessThanQuery")
            fi

            if [ ! -z "$fileContentQuery" ]; then
                findCmd+=("${fileContentQuery[@]}")
            fi

            searchQuery=$(find "${findCmd[@]}")

            if [ -z "$searchQuery" ]; then
                echo "File NOT found"
            else
                echo "File has been found"
            fi
            ;;

        7|"7.")
            userInput=7
            ;;
    esac
done
