      SUBROUTINE ALLOCH                                                         
C
C  Allokiert Ein- und Ausgabe - Datensaetze fuer HIVAP                               
C  (Einheit 21 wird in halloc.f allokiert)
C  Stand:  3.5.1994                                                                    
C
C     UNUSED: IST
      INTEGER*4 IST
      INTEGER*4 KST
      OPEN(5,FILE=
     1 '/mnt/f/code/nuclear-calculator/GUI/Hivap/hivapein.dat'
     1 ,STATUS='OLD',IOSTAT=KST)

      OPEN(6,FILE=
     1 '/mnt/f/code/nuclear-calculator/GUI/Hivap/hivaperg.dat'
     1 ,STATUS='UNKNOWN')
      OPEN(9,FILE=
     1 '/mnt/f/code/nuclear-calculator/GUI/Hivap/mlz.dat'
     1 ,STATUS='OLD')
      OPEN(10, ACCESS='SEQUENTIAL', STATUS='SCRATCH' )                            
      OPEN(11, ACCESS='SEQUENTIAL', STATUS='SCRATCH' )                                 
      OPEN(12, ACCESS='SEQUENTIAL', STATUS='SCRATCH' )                                 
      OPEN(13, ACCESS='SEQUENTIAL', STATUS='SCRATCH' )                                  
      OPEN(14,FILE=
     1 '/mnt/f/code/nuclear-calculator/GUI/Hivap/dummi1.dat'
     1 ,STATUS='UNKNOWN')
      OPEN(15,FILE=
     1 '/mnt/f/code/nuclear-calculator/GUI/Hivap/dummi2.dat',
     1 STATUS='UNKNOWN')
      OPEN(16,FILE=
     1 '/mnt/f/code/nuclear-calculator/GUI/Hivap/dummi3.dat'
     1 ,STATUS='UNKNOWN')
      OPEN(19,FILE=
     1 '/mnt/f/code/nuclear-calculator/GUI/Hivap/dummi4.dat'
     1 ,STATUS='UNKNOWN')
      OPEN(22,FILE=
     1 '/mnt/f/code/nuclear-calculator/GUI/Hivap/dummi6.dat'
     1 ,STATUS='UNKNOWN')
      OPEN(23,FILE=
     1 '/mnt/f/code/nuclear-calculator/GUI/Hivap/hivapaus.dat'
     1 ,STATUS='UNKNOWN')
      OPEN(25,FILE=
     1 '/mnt/f/code/nuclear-calculator/GUI/Hivap/dummi7.dat'
     1 ,STATUS='UNKNOWN')
      RETURN                                                                    
      END                                                                       
