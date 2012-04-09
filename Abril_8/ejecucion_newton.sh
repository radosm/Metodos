typeset -i i
i=1
while [ $i -lt 53 ]
do
#             precision  tolerancia  max_iter  altura  velocidad  masa  cr  fr
#             ---------  ----------  --------  ------  ---------  ----  --  --
  ./newton    $i         0.00001     10000     0       10         2     0   1
  i=$i+1
done
i=1
while [ $i -lt 53 ]
do
#             precision  tolerancia  max_iter  altura  velocidad  masa  cr  fr
#             ---------  ----------  --------  ------  ---------  ----  --  --
  ./newton    $i         0.000001    10000     0       10         2     0   1
  i=$i+1
done
i=1
while [ $i -lt 53 ]
do
#             precision  tolerancia  max_iter  altura  velocidad  masa  cr  fr
#             ---------  ----------  --------  ------  ---------  ----  --  --
  ./newton    $i         0.0000001   10000     0       10         2     0   1
  i=$i+1
done
i=1
while [ $i -lt 53 ]
do
#             precision  tolerancia  max_iter  altura  velocidad  masa  cr  fr
#             ---------  ----------  --------  ------  ---------  ----  --  --
  ./newton    $i         0.00000001  10000     0       10         2     0   1
  i=$i+1
done
i=1
while [ $i -lt 53 ]
do
#             precision  tolerancia   max_iter  altura  velocidad  masa  cr  fr
#             ---------  -----------  --------  ------  ---------  ----  --  --
  ./newton    $i         0.000000001  10000     0       10         2     0   1
  i=$i+1
done
