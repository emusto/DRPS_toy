#include <iostream>
#include "DRPS_twodets.h"
using namespace std;


#if !defined(__CINT__) || defined (__MAKECINT__)
int main(int argc, char* argv[])
{
  char* myConfFile;
  char* myOutFile;
  int myzsteps;
  
  if (argc < 7) {
    cout << "Usage is -c <configfile> -o <outputfilename> -n <zsteps>\n";
    exit(0);
  } else { 

    
    for (int i = 1; i < argc-1; i=i+2) {
      if (strncmp (argv[i],"-c",2)==0) {
	
	myConfFile = argv[i + 1];
	
      } else if (strncmp (argv[i],"-o",2)==0) {
	myOutFile = argv[i + 1];
	
      }	else if (strncmp (argv[i],"-n",2)==0) {

	myzsteps = atoi(argv[i + 1]);
	
      } else {
	cout << "Not enough or invalid arguments, please try again.\n";
	cout << "Usage is -c <configfile> -o <outputfilename> -n <zsteps>\n";
	exit(0);
      }

      
    }

  }
  
  DRPS_twodets mycycle(myConfFile,myOutFile,myzsteps);
  
  for(int nstep=0; nstep<=myzsteps;nstep++){
    mycycle.Initialize(nstep);
    mycycle.Loop();
    mycycle.DrawAndSave(nstep);
    mycycle.SaveHistos();
   
  }
  mycycle.Finalize();
  return 0;

}
#endif
