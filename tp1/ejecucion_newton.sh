typeset -i i

echo
echo 'pr tolerancia             max_i 1er imp                it alt max                 it 2do imp                it'
echo -- ---------------------- ----- ---------------------- -- ----------------------- -- ---------------------- --
i=52
while [ $i -lt 53 ]
do
#             precision  tolerancia  max_iter  altura  velocidad  masa  cr  fr
#             ---------  ----------  --------  ------  ---------  ----  --  --
##  ./newton    $i         0.00000000001     100    1000   500         2     0   1
#  ./newton    $i         0.00000000001     100    000   100000000         2     0   1
  ./newton    $i         0.00000000001     1000    000   100000000         20     1   1
  i=$i+1
done
