# Attribution reporting solution using gramine 
This repo contains code for privacy preserving attribution reporting in a secure enclave.

For more details please refer to the paper: TODO

# Quickstart

For installation please check [gramine documentation](https://gramine.readthedocs.io/en/latest/quickstart.html)
Check installation is correct and run: 
```
gramine-sgx
```


# Building

## Building for Linux

Run `make` (non-debug) or `make DEBUG=1` (debug) in the directory.

## Building for SGX

Run `make SGX=1` (non-debug) or `make SGX=1 DEBUG=1` (debug) in the directory.

# Run Attribution with Gramine

Without SGX:
```sh
gramine-direct main
```

With SGX:
```sh
gramine-sgx main
```


# Run multiple tests
Some scripts can be used to run multiple tests. For these scipts to work, you need to follow these steps: 
 - Clone input repo 
 ```
 git clone https://github.com/victormassy/input.git
 ```
 
 - Unzip input:
 
```
cd input
unzip TODO
```

 - Run tests:
``` 
chmod +x 100tests.sh 
./100tests.sh 
```

Execution times are stored in file results.txt in microseconds (ms). 


# Structure of the repo 

main.c: Contains code executed inside the enclave. 

wrap_key: cryptographic key used for encryption (the matching private key is hard coded in the manifest)

main.manifest.template: specify where to find encrypted input
