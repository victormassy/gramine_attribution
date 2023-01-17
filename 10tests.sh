echo -----Data set number $2----
cp input/gramine_rep_$1_v_$2.txt input.txt
gramine-sgx-pf-crypt encrypt -w wrap_key -i input.txt -o enc_files/input.txt
for i in {1..10} ; do
         ./graminee2e.sh
 done
