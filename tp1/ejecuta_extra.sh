for pr in 10
do
  for fr in 0.25 0.5 0.75 1
  do
    for cr in 1 2 3 4 5 6 7 8 9 10
    do
      ./extra $pr .00001 10000 19.62 0 1 $cr $fr
    done
  done
done

exit 
for pr in 52
do
  for fr in 1
  do
    for cr in 0.05 0.1 0.15 0.2 0.25 0.3 0.35 0.4 0.45 0.5
    do
      ./extra $pr .00001 10000 19.62 0 1 $cr $fr
    done
  done
done

exit 

##
##typeset -i i
##i=2
##while [ $i -lt 53 ]
##do
  ##./extra $i .00001 10000 19.62 0 1 0.5 0.75
  ##i=$i+1
##done
##
##exit




##i=52
##while [ $i -lt 53 ]
##do
#             precision  tolerancia  max_iter  altura  velocidad  masa  cr  fr
#             ---------  ----------  --------  ------  ---------  ----  --  --
##  ./newton    $i         0.00000000001     100    1000   500         2     0   1
#  ./newton    $i         0.00000000001     100    000   100000000         2     0   1
  ##./newton    $i         0.00000000001     1000    000   1000000         20     1   1
  ##i=$i+1
##done


 for pr in 52 10
do
  for fr in 1
  do
    for cr in 0.25 0.5 1 10 51 100 150 200
    do
      ./extra $pr .00001 10000 19.62 0 1 $cr $fr
    done
  done
done

for pr in 52 10
do
  for fr in  0.25 0.5 0.75
  do
    for cr in 0 0.25 0.5 1 10 51 100 150 200
    do
      ./extra $pr .00001 10000 19.62 0 1 $cr $fr
    done
  done
done

