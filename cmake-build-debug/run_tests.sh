echo "staff test:"
./hw2 < ../tests/in2.txt > ../tests/output.txt
diff ../tests/output.txt ../tests/out2.txt
echo "in_1:"
./hw2 < ../tests/in_1.txt > ../tests/output.txt
diff ../tests/output.txt ../tests/out_1.txt
echo "in_2:"
./hw2 < ../tests/in_2.txt > ../tests/output.txt
diff ../tests/output.txt ../tests/out_2.txt
echo "in_3:"
./hw2 < ../tests/in_3.txt > ../tests/output.txt
diff ../tests/output.txt ../tests/out_3.txt
echo "in_4:"
./hw2 < ../tests/in_4.txt > ../tests/output.txt
diff ../tests/output.txt ../tests/out_4.txt
echo "in_5:"
./hw2 < ../tests/in_5.txt > ../tests/output.txt
diff ../tests/output.txt ../tests/out_5.txt
echo "in_:6"
./hw2 < ../tests/in_6.txt > ../tests/output.txt
diff ../tests/output.txt ../tests/out_6.txt
