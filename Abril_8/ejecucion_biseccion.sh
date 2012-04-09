typeset -i i
i=1
while [ $i -lt 53 ]
do
#             precision  tolerancia  max_iter  altura  velocidad  masa  cr  fr
#             ---------  ----------  --------  ------  ---------  ----  --  --
  ./biseccion $i         0.0001      10000     0       10         2     0   1
  i=$i+1
done
