# Attribution reporting solution using gramine 
This repo contains code for privacy preserving attribution reporting in a secure enclave.

For more details please refer to the paper: TODO

# Building

## Building for Linux

Run `make` (non-debug) or `make DEBUG=1` (debug) in the directory.

## Building for SGX

Run `make SGX=1` (non-debug) or `make SGX=1 DEBUG=1` (debug) in the directory.

# Run Hello World with Gramine

Without SGX:
```sh
gramine-direct main
```

With SGX:
```sh
gramine-sgx main
```
