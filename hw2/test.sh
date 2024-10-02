#!/bin/bash
# write a shell scritps to compare the output with the real answers 
# Compile the program g++ -std=c++11 -o hw2_110550088 hw2_110550088.cpp 
# Run the program and compare the output 
total=1000 
correct=0 
echo "" > check.txt
for i in {1..1000}; do 
echo ”Test $i“ 
./hw2_110550168 < /home/os/os/hw2/mytestcase/testcase/tc_$i.txt > output.txt 
res=$(diff output.txt /home/os/os/hw2/mytestcase/ans/ans_$i.txt) 
#echo $res
if [ ”$res“ == ”“ ];
 then 
echo ”Correct“ 
correct=$((correct+1)) 
else 
echo ”Wrong“
 echo ”Your output:“ 
 cat output.txt 
echo ”Correct answer:“ 
cat /home/os/os/hw2/mytestcase/ans/ans_$i.txt
echo "${i}" >> check.txt
 fi 
 echo ---------
done
 #rm output.txt 
 echo ”Total: $correct/$total“

