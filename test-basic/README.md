<h1>Testing Basic NUCLEO dengan MBED</h1>

<h2>Testing terdiri dari</h2>

1. Blinking LED
2. Serial printf
3. Timer dengan us_ticker_read()

<h2>Commands:</h2>

Membuat Project baru (Di directory dengan mbed-os):
```
mbed-tools new -c <NAMA_PROJECT>
```
Mbed Configure:
```
mbed-tools configure -m NUCLEO_F446R -t GCC_ARM --mbed-os-path "../mbed-os" 
```
Build CMake:
```
cmake -S . -B cmake_build/NUCLEO_G071RB/develop/GCC_ARM -GNinja 
```
Build Ninja:
```
ninja -C cmake_build/NUCLEO_G071RB/develop/GCC_ARM
```