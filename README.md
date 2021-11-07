# Salsa20
Implementation of a stream cipher Salsa20

### Benchmarks

|      Standart    |     1 MB    |    10 MB    |   100 MB   |    1 GB        |
|       :---:      |    :----:   |     :---:   |     :--:   |    :---:       | 
|        Salsa20       |   0m0.048s  |   0m0.498s  |  0m5.168s  |   0m54.066s    |



### Compiling


```
git clone https://github.com/yhetman/Salsa20
cd Salsa20
make
```

To reocompile the code use:

```
make re
```

### Usage

```
./salsa20 -i ./input_file -o ./output_file -k ./key_file -n ./nonce_file -e | -d
```

Several flags are available:
`-e` - to start encrypting process (is used by default);
`-d` - to start dencrypting process;
`-h` - display help message.
