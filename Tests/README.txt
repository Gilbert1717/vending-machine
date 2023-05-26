To run the tests, copy the precompiled ppd file into each test directory(test1, test2 etc.).

Then run 

"./ppd stock.dat coins.dat < test#.input > test#.actual_ppd_out"

 replacing the '#' with the test number.

To verify if the out put is correct, run

"diff -w test#.output test#.actual_ppd_out"
"diff -w stock.dat test#.expstock"
"diff -w coins.dat test#.expcoins"

replacing the '#' with the test number.

The food category has been added to the end of each stock line due to the 2d linked-list implementation

Test 1 - reset coins and stocks
Test 2 - purchase I0005
Test 3 - add pizza under the food category
Test 4 - remove dessert I0003
Test 5 - remove Pie I0002 then add Pizza
Test 6 - purchase and abort program without saving
