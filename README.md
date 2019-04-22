# koko_skiplist
If you use eclipse to code, you will find there is a lot of reminder.
There is no comment on your code. It is hard to read without comments. Also you will forget what it is for after one week.


======== for main.cpp ===========

1. The main function need a return() as you defined it.
2. why include skipList.h. The class you use is in skipList.cpp. 
		solution 1: combin skip_list.cpp and skip_list.h as skip_list.h
		solution 2: move main funtion into skip_list.cpp


======== for skipList.cpp ===========

1. I prefer put the class' function in the same file with the class definition
2. #include "skiplist.h" should be #include "skipList.h"



Complie:
g++ -std=c++11 run.cpp -o run

Run:
./run
