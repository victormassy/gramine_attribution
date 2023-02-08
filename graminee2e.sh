make clean --silent
make SGX=1 --silent
taskset -c 0 gramine-sgx main >> results.txt
