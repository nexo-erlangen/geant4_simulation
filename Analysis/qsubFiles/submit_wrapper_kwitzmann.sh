#!/bin/bash -l
home=/home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/qsubFiles/submit_seriell.sh
executable=Simulation
config1="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/ -refl 1.000000 -alrefl 1.000000 -data Run_10_10"
config2="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 1.000000 -alrefl 0.900000 -data Run_10_9"
config3="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 1.000000 -alrefl 0.800000 -data Run_10_8"
config4="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 1.000000 -alrefl 0.700000 -data Run_10_7"
config5="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 1.000000 -alrefl 0.600000 -data Run_10_6"
config6="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 1.000000 -alrefl 0.500000 -data Run_10_5"
config7="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 1.000000 -alrefl 0.400000 -data Run_10_4"
config8="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 1.000000 -alrefl 0.300000 -data Run_10_3"
config9="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 1.000000 -alrefl 0.200000 -data Run_10_2"
config10="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 1.000000 -alrefl 0.100000 -data Run_10_1"
config11="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 1.000000 -alrefl 0.000000 -data Run_10_0"
config12="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.900000 -alrefl 1.000000 -data Run_9_10"
config13="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.900000 -alrefl 0.900000 -data Run_9_9"
config14="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.900000 -alrefl 0.800000 -data Run_9_8"
config15="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.900000 -alrefl 0.700000 -data Run_9_7"
config16="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.900000 -alrefl 0.600000 -data Run_9_6"
config17="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.900000 -alrefl 0.500000 -data Run_9_5"
config18="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.900000 -alrefl 0.400000 -data Run_9_4"
config19="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.900000 -alrefl 0.300000 -data Run_9_3"
config20="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.900000 -alrefl 0.200000 -data Run_9_2"
config21="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.900000 -alrefl 0.100000 -data Run_9_1"
config22="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.900000 -alrefl 0.000000 -data Run_9_0"
config23="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.800000 -alrefl 1.000000 -data Run_8_10"
config24="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.800000 -alrefl 0.900000 -data Run_8_9"
config25="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.800000 -alrefl 0.800000 -data Run_8_8"
config26="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.800000 -alrefl 0.700000 -data Run_8_7"
config27="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.800000 -alrefl 0.600000 -data Run_8_6"
config28="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.800000 -alrefl 0.500000 -data Run_8_5"
config29="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.800000 -alrefl 0.400000 -data Run_8_4"
config30="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.800000 -alrefl 0.300000 -data Run_8_3"
config31="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.800000 -alrefl 0.200000 -data Run_8_2"
config32="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.800000 -alrefl 0.100000 -data Run_8_1"
config33="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.800000 -alrefl 0.000000 -data Run_8_0"
config34="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.700000 -alrefl 1.000000 -data Run_7_10"
config35="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.700000 -alrefl 0.900000 -data Run_7_9"
config36="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.700000 -alrefl 0.800000 -data Run_7_8"
config37="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.700000 -alrefl 0.700000 -data Run_7_7"
config38="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.700000 -alrefl 0.600000 -data Run_7_6"
config39="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.700000 -alrefl 0.500000 -data Run_7_5"
config40="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.700000 -alrefl 0.400000 -data Run_7_4"
config41="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.700000 -alrefl 0.300000 -data Run_7_3"
config42="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.700000 -alrefl 0.200000 -data Run_7_2"
config43="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.700000 -alrefl 0.100000 -data Run_7_1"
config44="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.700000 -alrefl 0.000000 -data Run_7_0"
config45="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.600000 -alrefl 1.000000 -data Run_6_10"
config46="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.600000 -alrefl 0.900000 -data Run_6_9"
config47="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.600000 -alrefl 0.800000 -data Run_6_8"
config48="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.600000 -alrefl 0.700000 -data Run_6_7"
config49="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.600000 -alrefl 0.600000 -data Run_6_6"
config50="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.600000 -alrefl 0.500000 -data Run_6_5"
config51="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.600000 -alrefl 0.400000 -data Run_6_4"
config52="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.600000 -alrefl 0.300000 -data Run_6_3"
config53="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.600000 -alrefl 0.200000 -data Run_6_2"
config54="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.600000 -alrefl 0.100000 -data Run_6_1"
config55="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.600000 -alrefl 0.000000 -data Run_6_0"
config56="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.500000 -alrefl 1.000000 -data Run_5_10"
config57="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.500000 -alrefl 0.900000 -data Run_5_9"
config58="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.500000 -alrefl 0.800000 -data Run_5_8"
config59="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.500000 -alrefl 0.700000 -data Run_5_7"
config60="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.500000 -alrefl 0.600000 -data Run_5_6"
config61="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.500000 -alrefl 0.500000 -data Run_5_5"
config62="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.500000 -alrefl 0.400000 -data Run_5_4"
config63="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.500000 -alrefl 0.300000 -data Run_5_3"
config64="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.500000 -alrefl 0.200000 -data Run_5_2"
config65="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.500000 -alrefl 0.100000 -data Run_5_1"
config66="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.500000 -alrefl 0.000000 -data Run_5_0"
config67="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.400000 -alrefl 1.000000 -data Run_4_10"
config68="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.400000 -alrefl 0.900000 -data Run_4_9"
config69="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.400000 -alrefl 0.800000 -data Run_4_8"
config70="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.400000 -alrefl 0.700000 -data Run_4_7"
config71="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.400000 -alrefl 0.600000 -data Run_4_6"
config72="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.400000 -alrefl 0.500000 -data Run_4_5"
config73="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.400000 -alrefl 0.400000 -data Run_4_4"
config74="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.400000 -alrefl 0.300000 -data Run_4_3"
config75="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.400000 -alrefl 0.200000 -data Run_4_2"
config76="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.400000 -alrefl 0.100000 -data Run_4_1"
config77="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.400000 -alrefl 0.000000 -data Run_4_0"
config78="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.300000 -alrefl 1.000000 -data Run_3_10"
config79="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.300000 -alrefl 0.900000 -data Run_3_9"
config80="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.300000 -alrefl 0.800000 -data Run_3_8"
config81="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.300000 -alrefl 0.700000 -data Run_3_7"
config82="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.300000 -alrefl 0.600000 -data Run_3_6"
config83="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.300000 -alrefl 0.500000 -data Run_3_5"
config84="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.300000 -alrefl 0.400000 -data Run_3_4"
config85="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.300000 -alrefl 0.300000 -data Run_3_3"
config86="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.300000 -alrefl 0.200000 -data Run_3_2"
config87="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.300000 -alrefl 0.100000 -data Run_3_1"
config88="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.300000 -alrefl 0.000000 -data Run_3_0"
config89="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.200000 -alrefl 1.000000 -data Run_2_10"
config90="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.200000 -alrefl 0.900000 -data Run_2_9"
config91="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.200000 -alrefl 0.800000 -data Run_2_8"
config92="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.200000 -alrefl 0.700000 -data Run_2_7"
config93="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.200000 -alrefl 0.600000 -data Run_2_6"
config94="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.200000 -alrefl 0.500000 -data Run_2_5"
config95="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.200000 -alrefl 0.400000 -data Run_2_4"
config96="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.200000 -alrefl 0.300000 -data Run_2_3"
config97="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.200000 -alrefl 0.200000 -data Run_2_2"
config98="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.200000 -alrefl 0.100000 -data Run_2_1"
config99="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.200000 -alrefl 0.000000 -data Run_2_0"
config100="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.100000 -alrefl 1.000000 -data Run_1_10"
config101="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.100000 -alrefl 0.900000 -data Run_1_9"
config102="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.100000 -alrefl 0.800000 -data Run_1_8"
config103="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.100000 -alrefl 0.700000 -data Run_1_7"
config104="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.100000 -alrefl 0.600000 -data Run_1_6"
config105="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.100000 -alrefl 0.500000 -data Run_1_5"
config106="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.100000 -alrefl 0.400000 -data Run_1_4"
config107="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.100000 -alrefl 0.300000 -data Run_1_3"
config108="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.100000 -alrefl 0.200000 -data Run_1_2"
config109="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.100000 -alrefl 0.100000 -data Run_1_1"
config110="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.100000 -alrefl 0.000000 -data Run_1_0"
config111="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.000000 -alrefl 1.000000 -data Run_0_10"
config112="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.000000 -alrefl 0.900000 -data Run_0_9"
config113="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.000000 -alrefl 0.800000 -data Run_0_8"
config114="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.000000 -alrefl 0.700000 -data Run_0_7"
config115="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.000000 -alrefl 0.600000 -data Run_0_6"
config116="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.000000 -alrefl 0.500000 -data Run_0_5"
config117="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.000000 -alrefl 0.400000 -data Run_0_4"
config118="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.000000 -alrefl 0.300000 -data Run_0_3"
config119="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.000000 -alrefl 0.200000 -data Run_0_2"
config120="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.000000 -alrefl 0.100000 -data Run_0_1"
config121="-SiPMHisto -PMTHisto -pressure 0.9 -numevents 25000 -path /home/hpc/capm/mppi005h/geant4_Rey_Dez_2016/Seventh/Analysis/Judith/  -refl 0.000000 -alrefl 0.000000 -data Run_0_0"
config122="-ErrorOnPurpose" 
config123="-ErrorOnPurpose" 
config124="-ErrorOnPurpose" 
qsub -v config1="$config1",config2="$config2",config3="$config3",config4="$config4",executable=$executable $home
qsub -v config1="$config5",config2="$config6",config3="$config7",config4="$config8",executable=$executable $home
qsub -v config1="$config9",config2="$config10",config3="$config11",config4="$config12",executable=$executable $home
qsub -v config1="$config13",config2="$config14",config3="$config15",config4="$config16",executable=$executable $home
qsub -v config1="$config17",config2="$config18",config3="$config19",config4="$config20",executable=$executable $home
qsub -v config1="$config21",config2="$config22",config3="$config23",config4="$config24",executable=$executable $home
qsub -v config1="$config25",config2="$config26",config3="$config27",config4="$config28",executable=$executable $home
qsub -v config1="$config29",config2="$config30",config3="$config31",config4="$config32",executable=$executable $home
qsub -v config1="$config33",config2="$config34",config3="$config35",config4="$config36",executable=$executable $home
qsub -v config1="$config37",config2="$config38",config3="$config39",config4="$config40",executable=$executable $home
qsub -v config1="$config41",config2="$config42",config3="$config43",config4="$config44",executable=$executable $home
qsub -v config1="$config45",config2="$config46",config3="$config47",config4="$config48",executable=$executable $home
qsub -v config1="$config49",config2="$config50",config3="$config51",config4="$config52",executable=$executable $home
qsub -v config1="$config53",config2="$config54",config3="$config55",config4="$config56",executable=$executable $home
qsub -v config1="$config57",config2="$config58",config3="$config59",config4="$config60",executable=$executable $home
qsub -v config1="$config61",config2="$config62",config3="$config63",config4="$config64",executable=$executable $home
qsub -v config1="$config65",config2="$config66",config3="$config67",config4="$config68",executable=$executable $home
qsub -v config1="$config69",config2="$config70",config3="$config71",config4="$config72",executable=$executable $home
qsub -v config1="$config73",config2="$config74",config3="$config75",config4="$config76",executable=$executable $home
qsub -v config1="$config77",config2="$config78",config3="$config79",config4="$config80",executable=$executable $home
qsub -v config1="$config81",config2="$config82",config3="$config83",config4="$config84",executable=$executable $home
qsub -v config1="$config85",config2="$config86",config3="$config87",config4="$config88",executable=$executable $home
qsub -v config1="$config89",config2="$config90",config3="$config91",config4="$config92",executable=$executable $home
qsub -v config1="$config93",config2="$config94",config3="$config95",config4="$config96",executable=$executable $home
qsub -v config1="$config97",config2="$config98",config3="$config99",config4="$config100",executable=$executable $home
qsub -v config1="$config101",config2="$config102",config3="$config103",config4="$config104",executable=$executable $home
qsub -v config1="$config105",config2="$config106",config3="$config107",config4="$config108",executable=$executable $home
qsub -v config1="$config109",config2="$config110",config3="$config111",config4="$config112",executable=$executable $home
qsub -v config1="$config113",config2="$config114",config3="$config115",config4="$config116",executable=$executable $home
qsub -v config1="$config117",config2="$config118",config3="$config119",config4="$config120",executable=$executable $home
qsub -v config1="$config121",config2="$config122",config3="$config123",config4="$config124",executable=$executable $home
