To run the tests, copy the precompiled ppd file into each test directory(test1, test2 etc.).

Then run 

"./ppd stock.dat coins.dat < test#.input > test#.actual_ppd_out"

 replacing the '#' with the test number.

To verify if the out put is correct, run

"diff -w test#.output test#.actual_ppd_out"
"diff -w stock.dat test#.expstock"
"diff -w coins.dat test#.expcoins"

replacing the '#' with the test number.

