for((;;))
do
	./make > test.txt
	./test < test.txt > ans.txt
	./4515 < test.txt > 1011.txt
	if diff ans.txt 1011.txt;then
		echo OK
	else
		echo !
		exit
	fi
done