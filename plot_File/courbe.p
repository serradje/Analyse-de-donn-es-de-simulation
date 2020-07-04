set terminal pdf
set output 'courbe.pdf'


set xlabel "Time (s)"
set ylabel "Nombre de Paquets"
#set key 0.01,100

plot "plot_File/file_attente.tr" using 1:2 with lines title "Nombre de paquets en attente dans la file cours du temps"
plot "plot_File/transit.tr" using 1:2 with lines title "Nombre de Paquets en Transit au cours du Temps"  
plot "plot_File/perdu.tr" using 1:2 with lines title "Nombre de paquet perdu au cours de temps"

set xlabel "Nombre de Paquets"
set ylabel "Time (s)"
#set key 0.01,100
plot "plot_File/delai_flux.tr" using 2:1 with lines title "Delai de Bout en Bout pour les Paquets au cours du Temps"

set xlabel "Time (s)"
set ylabel "Nombre de flux actif"
plot "plot_File/flux_actif.tr" using 1:2 with lines title "Nombre de Flux Actif au cours du Temps"
