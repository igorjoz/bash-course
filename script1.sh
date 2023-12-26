#!/bin/bash

grep "OK DOWNLOAD" cdlinux.ftp.log | cut -d'"' -f 2,4 | sort -u | sed "1,\$s#.*/##" | grep "\.iso" > downloadsData.txt


cut -d" " -f 1,7,9 cdlinux.www.log | grep ' 200$' | sort | uniq | cut -d " " -f 2 | grep '\.iso' | grep -o "cdlinux-.*" | sed "s#?.*##" >> downloadsData.txt

cat < downloadsData.txt | sort | uniq -c | sort > result.txt
