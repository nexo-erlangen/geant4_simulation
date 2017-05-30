#rm -r B1-build
mkdir Simulation7.0-build
cd src/
rm ._*
cd ..
cd include/
rm ._*
cd ..
cd Simulation7.0-build/
cmake -DGeant4_DIR=~/geant.4.10_install/lib64/Geant4-10.2.0 ~/geant4_Rey_Dez_2016/Seventh/

make

./Simulation 