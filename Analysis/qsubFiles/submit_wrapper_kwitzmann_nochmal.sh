#!/bin/bash -l
home=/home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/qsubFiles/submit_seriell.sh
executable=Simulation
config1="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/ -refl 1.000000 -alrefl 1.000000 -data Run_10_10"
config2="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 1.000000 -alrefl 0.900000 -data Run_10_9"
config3="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 1.000000 -alrefl 0.800000 -data Run_10_8"
config4="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 1.000000 -alrefl 0.700000 -data Run_10_7"
config5="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 1.000000 -alrefl 0.600000 -data Run_10_6"
config6="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.900000 -alrefl 1.000000 -data Run_9_10"
config7="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.900000 -alrefl 0.900000 -data Run_9_9"
config8="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.900000 -alrefl 0.800000 -data Run_9_8"
config9="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.900000 -alrefl 0.700000 -data Run_9_7"
config10="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.900000 -alrefl 0.600000 -data Run_9_6"
config11="-ErrorOnPurpose" 
config12="-ErrorOnPurpose" 
qsub -v config1="$config1",config2="$config2",config3="$config3",config4="$config4",executable=$executable $home
qsub -v config1="$config5",config2="$config6",config3="$config7",config4="$config8",executable=$executable $home
qsub -v config1="$config9",config2="$config10",config3="$config11",config4="$config12",executable=$executable $home
