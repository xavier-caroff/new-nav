# How to build

## Build boost manually

Download boost sources from the web site http://boost.org

```bash
sudo apt-get install icu-devtools
./bootstrap.sh
./b2 --prefix=/home/xca/TOOLS/boost_1_69_0 --build-dir=/home/xca/DEV/boost_1_69_0_build --with-date_time --with-filesystem --with-program_options --with-regex --with-system --with-thread
```

