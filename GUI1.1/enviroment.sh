rm EnviromentTmp.txt
pwd >> EnviromentTmp.txt
g++ hivapEnviroment.cpp -o hivapEnviroment
./hivapEnviroment
cd ./Hivap
make clean
make
cd  ..
rm ./hivapEnviroment
rm EnviromentTmp.txt
