##### 1.	Executing pythonCounter.cpp:
```sh
g++ -o output pythonCounter.cpp 
./output
```

##### 2.	Compiling the code (with boost):
```sh
g++ -I /usr/local/Cellar/boost/1.62.0/include -L /usr/local/Cellar/boost/1.62.0/lib ./src/*.cpp -o UCC -DUNIX -pthread -O3 -lboost_thread-mt -lboost_regex-mt -lboost_system-mt
```
