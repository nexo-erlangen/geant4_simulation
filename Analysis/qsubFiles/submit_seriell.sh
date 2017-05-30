#!/bin/bash -l
#PBS -l nodes=1:ppn=4:any,walltime=0:23:50:00
#PBS -M katharina.witzmann@fau.de -m abe
#PBS -N For_Judith_nochmal
#PBS -o /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/qsubFiles/seriell.out -e /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/qsubFiles/seriell.err
cd  /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Simulation7.0-build
echo -e -n "Start:\t" && date
module load gnuplot/4.6.1
module list
module load CLHEP
module load qt/4.8.6
module load cmake/3.4.3
source /home/hpc/capm/mppi005h/geant4.10_install/bin/geant4.sh
echo '(taskset -c 0 ./'$executable ' '$config1' )'
(taskset -c 0 ./$executable $config1)&
(taskset -c 1 ./$executable $config2)&
(taskset -c 2 ./$executable $config3)&
(taskset -c 3 ./$executable $config4)&
wait
echo -e -n "Ende:\t" && date
