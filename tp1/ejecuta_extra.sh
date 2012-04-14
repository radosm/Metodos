 for pr in 52 10
do
  for fr in 1
  do
    for cr in 1 10 51 100 150 200
    do
      ./extra $pr .00001 10000 19.62 0 1 $cr $fr
    done
  done
done

for pr in 52 10
do
  for fr in  0.25 0.5 0.75
  do
    for cr in 0 1 10 51 100 150 200
    do
      ./extra $pr .00001 10000 19.62 0 1 $cr $fr
    done
  done
done
