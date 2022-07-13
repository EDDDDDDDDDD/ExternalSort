# External Sort
c++

__ExternalMemorySort.cpp will generate emp_buf*.csv files as middle files.__
__The result will be stored in EmpSorted.csv.__

The number of the middle files depends on the data amount.

The algorithm will divide the data into 21 blocks.

i.e. The data amount is 700. It will be 700/21 -> 33/21 -> final result. Thus, there will be two middle files.

## Database format

***Emp (eid (integer), ename (string), age (integer), salary (double))***
