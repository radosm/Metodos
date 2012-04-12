typeset -i i
i=52

echo
echo 'pr tolerancia             max_i 1er imp                it alt max                 it 2do imp                it'
echo -- ---------------------- ----- ---------------------- -- ----------------------- -- ---------------------- --

##for cr in 0 0.6 1 13
##do
  ##for fr in 0 0.5 1
  ##do
    ##for altura in 100 1000 10000
    ##do
      ##for velocidad in 0 -10 10
      ##do
###                      precision  tolerancia  max_iter  altura  velocidad  masa  cr  fr
###                      ---------  ----------  --------  ------  ---------  ----- --- ---
        ##echo "altura="$altura" velocidad="$velocidad" masa=2 cr="$cr" fr="$fr
        ##./biseccion 52 0.00001 1000 $altura $velocidad 2 $cr $fr
      ##done
    ##done
  ##done
##done 
##
while [ $i -lt 53 ]
do
#             precision  tolerancia  max_iter  altura  velocidad  masa  cr  fr
#             ---------  ----------  --------  ------  ---------  ----  --  --
  ./biseccion $i         0.00000000001     100    1000   500         2     0   1
  i=$i+1
done

echo
