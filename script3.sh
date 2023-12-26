#!/bin/bash

userInput=0

fileName=
directoryName=
fileSizeGreaterThan=
fileSizeLessThan=
fileContent=

while [ "$userInput" != 7 ]; do
option1="1. File name (with extension): $fileName"
option2="2. Directory name: $directoryName"
option3="3. Greater than (file size, bytes): $fileSizeGreaterThan"
option4="4. Less than (file size, bytes): $fileSizeLessThan"
option5="5. Content: $fileContent"
option6="6. Run search: " 
option7="7. Quit: " 

menuOptions=("$option1" "$option2" "$option3" "$option4" "$option5" "$option6" "$option7")
    userInput=$(zenity --list --column=Menu "${menuOptions[@]}" --height 400)

case "$userInput" in
        $option1)
            fileName=$(zenity --entry --title "File finder" --text "File name: ")
            fileNameQuery="-name $fileName"
            if [ -z $fileName ]
            then
            fileNameQuery=""
            fi
            ;;

        $option2)
            directoryName=$(zenity --entry --title "File finder" --text "Directory name: ")
            directoryNameQuery="./${directoryName}"
            if [ -z $directoryName ]
            then
            directoryNameQuery=""
            fi
            ;;

       $option3)
            fileSizeGreaterThan=$(zenity --entry --title "File finder" --text "Minimal file size: ")
            fileSizeGreaterThanQuery="-size +${fileSizeGreaterThan}c"
            if [ -z $fileSizeGreaterThan ]
            then
            fileSizeGreaterThanQuery=""
            fi
            ;;

        $option4)
            fileSizeLessThan=$(zenity --entry --title "File finder" --text "Maimal file size: ")
            fileSizeLessThanQuery="-size -${fileSizeLessThan}c"
            if [ -z $fileSizeLessThan ]
            then
            fileSizeLessThanQuery=""
            fi
            ;;

        $option5)
            fileContent=$(zenity --entry --title "File finder" --text "File content: ")
            fileContentQuery="-exec grep -l \"$fileContent\" {} \;"
            if [ -z "$fileContent" ]
            then
            fileContentQuery=""
            fi
            ;;
    
        $option6)
            result=$(find $directoryNameQuery -type f $fileNameQuery $fileSizeGreaterThanQuery $fileSizeLessThanQuery $fileContentQuery)
            if [ -z "$result" ]; then
              zenity --info --text="No files found." --title="Search Results"
            else
              echo "$result" | zenity --text-info --title "Found files" --width 500
            fi
            ;;

        $option7)
            userInput=7
            ;;
    esac
done
