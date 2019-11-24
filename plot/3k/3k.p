set terminal png size 5900,500 
set output 'output.png'

red = "#FF0000"; green = "#7CFC00"; blue = "#1E90FF";
set yrange [0:600]
set style data histogram
set style histogram cluster gap 1
set style fill transparent solid 0.3
set boxwidth 0.1
set xtics format ""
set grid ytics

set title "K-means Clustering for 3 cluster"
plot "sample3K_c1.txt" using 2:xtic(1) title "Cluster-1" linecolor rgb red,\
	 "sample3K_c2.txt" using 2:xtic(1) title "Cluster-2" linecolor rgb green, \
	 "sample3K_c3.txt" using 2:xtic(1) title "Cluster-3" linecolor rgb blue