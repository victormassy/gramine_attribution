# Attribution reporting in a secure enclave

This directory contains TODO

# Building

## Building for Linux

Run `make` (non-debug) or `make DEBUG=1` (debug) in the directory.

## Building for SGX

Run `make SGX=1` (non-debug) or `make SGX=1 DEBUG=1` (debug) in the directory.

# Run Hello World with Gramine

Without SGX:
```sh
gramine-direct helloworld
```

With SGX:
```sh
gramine-sgx helloworld
```
