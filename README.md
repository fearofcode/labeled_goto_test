how to build:

- Install conan

- 
```
mkdir build
cd build
conan install ..
cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake --build .
./bin/labeled_goto_test
```

Sample output:

```
warren@stampy:~/CLionProjects/labeled_goto_test/build$ ./bin/labeled_goto_test 
2021-01-02T22:25:16-08:00
Running ./bin/labeled_goto_test
Run on (16 X 3600 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x8)
  L1 Instruction 32 KiB (x8)
  L2 Unified 512 KiB (x8)
  L3 Unified 16384 KiB (x2)
Load Average: 0.45, 0.45, 0.42
***WARNING*** CPU scaling is enabled, the benchmark real time measurements may be noisy and will incur extra overhead.
----------------------------------------------------------
Benchmark                Time             CPU   Iterations
----------------------------------------------------------
BM_SwitchTable        76.6 ns         76.6 ns      9030936
BM_ComputedGoto       54.8 ns         54.8 ns     12533042
```