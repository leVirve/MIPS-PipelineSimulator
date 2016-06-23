red=`tput setaf 1`
green=`tput setaf 2`
reset=`tput sgr0`

passes=0
counter=0

while read tcase; do
    flag=0
    timeout 3 ./pipeline ./testcase/$tcase/iimage.bin ./testcase/$tcase/dimage.bin > /dev/null
    if ! diff --strip-trailing-cr ./testcase/$tcase/snapshot.rpt snapshot.rpt > /dev/null ; then
        flag=1
        echo $tcase: ${red}Fail on snapshot${reset}
    fi
    if ! diff --strip-trailing-cr ./testcase/$tcase/error_dump.rpt error_dump.rpt > /dev/null ; then
        if [ $flag -eq 0 ]; then
            flag=1
            echo $tcase: ${red}Fail on error_dump${reset}
        fi
    fi
    if [ $flag -eq 0 ]; then
        echo $tcase: ${green}Pass!${reset}
        passes=$((passes+1))
    fi
    counter=$((counter+1))
done < testcase_list

echo ${green}Pass: $passes / $counter${reset}
