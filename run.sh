while read tcase; do
# cp ./testcase/$tcase/iimage.bin iimage.bin
# cp ./testcase/$tcase/dimage.bin dimage.bin
echo "== Testing on" $tcase "=="
timeout 3 ./pipeline ./testcase/$tcase/iimage.bin ./testcase/$tcase/dimage.bin > /dev/null
if ! diff --strip-trailing-cr ./testcase/$tcase/snapshot.rpt snapshot.rpt > /dev/null ; then
	set flag = 1
	echo fail $tcase: snapshot
fi
if ! diff --strip-trailing-cr ./testcase/$tcase/error_dump.rpt error_dump.rpt > /dev/null ; then
	if ! $flag ; then
		echo fail $tcase
	fi
fi
done < testcase_list
