typeset -i i

i=52
while [ $i -lt 53 ]
do
  for cr in 0 1 2 3 4
  do
  #             precision  tolerancia     max_iter  altura  velocidad  masa  cr   fr
  #             ---------  -------------  --------  ------  ---------  ----  --   --
    ./newton    $i         0.00000000001  100       1000    500        2     $cr  1   | grep ^em |cut -d" " -f 2,3 > cr.$cr
  done
  i=$i+1
done
