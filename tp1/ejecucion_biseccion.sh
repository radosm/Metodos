rm -f resultado_biseccion.*

for cr in 0 0.6 1 13
do
  for fr in 0 0.25 0.5 0.75 1
  do
    for altura in 0.10 100 1000 10000
    do
      for velocidad in 0 -10 10 -381 1000000
      do
        for pr in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52
        do
          ./biseccion $pr 0.00001 1000 $altura $velocidad 2 $cr $fr  >> resultado_biseccion.h${altura}_v${velocidad}_m2_cr${cr}_fr${fr}
        done
      done
    done
  done 
done

##while [ $i -lt 53 ]
##do
#             precision  tolerancia  max_iter  altura  velocidad  masa  cr  fr
#             ---------  ----------  --------  ------  ---------  ----  --  --
#  ./biseccion $i         0.00000000001     100    1000   500         2     0   1
##  ./biseccion $i         0.00000000001     100000    000   100000000         20     1   1
##  i=$i+1
##done

echo
