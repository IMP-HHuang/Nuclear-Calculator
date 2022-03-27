#include "iostream"
#include "fstream"
#include "string"

int main()
{
	std::ifstream fin;
	fin.open("EnviromentTmp.txt");
	std::string stmp;
	fin >> stmp;
	fin.close();
	std::ofstream fout;
	fout.open("./Hivap/alloch.f");
	fout <<"      SUBROUTINE ALLOCH" << std::endl;                                                         
	fout << "C" << std::endl;  
	fout << "C  Allokiert Ein- und Ausgabe - Datensaetze fuer HIVAP " << std::endl;                                
	fout << "C  (Einheit 21 wird in halloc.f allokiert)" << std::endl;  
	fout << "C  Stand:  3.5.1994 " << std::endl;                                                                     
	fout << "C" << std::endl;  
	fout << "C      UNUSED: IST" << std::endl;  
	fout << "      INTEGER*4 IST" << std::endl;  
	fout << "      INTEGER*4 KST" << std::endl;  
	fout << "      OPEN(5,FILE=" << std::endl;  
	fout << "     1 '"<<stmp<<"/Hivap/hivapein.dat'" << std::endl;  
	fout << "     1 ,STATUS='OLD',IOSTAT=KST)" << std::endl;  
	fout << "" << std::endl;  
	fout << "      OPEN(6,FILE=" << std::endl;  
	fout << "     1 '" << stmp << "/Hivap/hivaperg.dat'" << std::endl;  
	fout << "     1 ,STATUS='UNKNOWN')" << std::endl;  
	fout << "      OPEN(9,FILE=" << std::endl;  
	fout << "     1 '" << stmp << "/Hivap/mlz.dat'" << std::endl;  
	fout << "     1 ,STATUS='OLD')" << std::endl;  
	fout << "      OPEN(10, ACCESS='SEQUENTIAL', STATUS='SCRATCH' )" << std::endl;                              
	fout << "      OPEN(11, ACCESS='SEQUENTIAL', STATUS='SCRATCH' )" << std::endl;                                   
	fout << "      OPEN(12, ACCESS='SEQUENTIAL', STATUS='SCRATCH' )" << std::endl;                                   
	fout << "      OPEN(13, ACCESS='SEQUENTIAL', STATUS='SCRATCH' )" << std::endl;                                    
	fout << "      OPEN(14,FILE=" << std::endl;  
	fout << "     1 '" << stmp << "/Hivap/dummi1.dat'" << std::endl;  
	fout << "     1 ,STATUS='UNKNOWN')" << std::endl;  
	fout << "      OPEN(15,FILE=" << std::endl;  
	fout << "     1 '" << stmp << "/Hivap/dummi2.dat'," << std::endl;  
	fout << "     1 STATUS='UNKNOWN')" << std::endl;  
	fout << "      OPEN(16,FILE=" << std::endl;  
	fout << "     1 '" << stmp << "/Hivap/dummi3.dat'" << std::endl;  
	fout << "     1 ,STATUS='UNKNOWN')" << std::endl;  
	fout << "      OPEN(19,FILE=" << std::endl;  
	fout << "     1 '" << stmp << "/Hivap/dummi4.dat'" << std::endl;  
	fout << "     1 ,STATUS='UNKNOWN')" << std::endl;  
	fout << "      OPEN(22,FILE=" << std::endl;  
	fout << "     1 '" << stmp << "/Hivap/dummi6.dat'" << std::endl;  
	fout << "     1 ,STATUS='UNKNOWN')" << std::endl;  
	fout << "      OPEN(23,FILE=" << std::endl;  
	fout << "     1 '" << stmp << "/Hivap/hivapaus.dat'" << std::endl;  
	fout << "     1 ,STATUS='UNKNOWN')" << std::endl;  
	fout << "      OPEN(25,FILE=" << std::endl;  
	fout << "     1 '" << stmp << "/Hivap/dummi7.dat'" << std::endl;  
	fout << "     1 ,STATUS='UNKNOWN')" << std::endl;  
	fout << "      RETURN " << std::endl;                                                                     
	fout << "      END " << std::endl;         
	fout.close();
	return 0;
}	  
