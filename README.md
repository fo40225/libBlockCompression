# BlockCompression

## How to build

### Windows

- install [MSYS2](https://www.msys2.org/) [msys2-x86_64-20190524.exe](http://repo.msys2.org/distrib/x86_64/msys2-x86_64-20190524.exe)
- Start > MSYS2 64bit > MSYS2 MSYS
```shell
pacman -S --needed --noconfirm base base-devel msys2-devel libraries development \
                               editors compression sys-utils net-utils VCS Database \
                               mingw-w64-i686-toolchain mingw-w64-x86_64-toolchain
pacman -S cmake
exit
```
- Start > MSYS2 64bit > MSYS2 MinGW 64-bit
```shell
git config --global user.email "you@example.com"
git config --global user.name "Your Name"
alias make='mingw32-make'

git clone https://github.com/fo40225/BlockCompression.git
cd BlockCompression
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release && cmake --build . -v
```
- rename `build\BlockCompression\libBlockCompression.so` to `BlockCompression.dll`
