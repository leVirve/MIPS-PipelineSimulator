while read tcase; do
# echo run "case#" $tcase
cp ../testcase/$tcase/iimage.bin iimage.bin
cp ../testcase/$tcase/dimage.bin dimage.bin
timeout 3 ./pipeline > /dev/null
if ! diff ../testcase/$tcase/snapshot.rpt snapshot.rpt > /dev/null ; then
	set flag = 1
	echo fail $tcase: snapshot
fi
if ! diff ../testcase/$tcase/error_dump.rpt error_dump.rpt > /dev/null ; then
	if ! $flag ; then
		echo fail $tcase
	fi
fi
done < ../testcase_list
