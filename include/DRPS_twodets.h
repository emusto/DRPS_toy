/***************************************************************************
 * @Project: DRPS_TOY - ROOT-based analysis framework for SwissFEL DRPS    *
 *                                                                         *
 * @author Elisa Musto <Elisa.Musto@psi.ch> - Paul Scherrer Institute      *
 *                                                                         *
 * 12/10/2015                                                              *
 ***************************************************************************/

#ifndef DRPS_TWODETS_H
#define DRPS_TWODETS_H
#include "TROOT.h"
#include "TH2D.h"
#include "TTree.h"
#include "TTreeReader.h"
#include "TMath.h"
#include "TRandom3.h"
#include "TCanvas.h"
#include "TSystem.h"
#include "TStyle.h"
#include "TFile.h"
#include "TApplication.h"
#include "TLegend.h"
#include "RoofDetector.h"
#include "OutsideDetector.h"
#include "Logger.h"
#include "ConfigParser.h"
#include "Source.h"

#include <vector>

class DRPS_twodets{

 private:
  ConfigParser m_parser;
  char *m_output;
  string m_debuglevel;
  int m_nzsteps;
  
  map <string, string> m_options;
  mutable Logger m_logger;
  OutsideDetector * m_o1;
  OutsideDetector * m_o2;
  Source * m_s;
  void SetupDetectors();
  void SetupSource(int);
  void CreateOutput();
  TFile * m_f;
  TFile * outputHistosFile;
  TTree * OD1tree;
  TTree * OD2tree;
  //  TTreeReader MyReader;
  string m_id1;
  string m_id2;

  vector<float>  m_d01;
  vector<float>  m_d02;
  vector<float>  m_din1;
  vector<float>  m_din2;
  vector<float>  m_drin1;
  vector<float>  m_drin2;
  vector<float>  m_drout1;
  vector<float>  m_drout2;
  vector<float>  m_drin1_1s;
  vector<float>  m_drin2_1s;
  vector<float>  m_drout1_1s;
  vector<float>  m_drout2_1s;
  vector<float>  m_drin1_1m;
  vector<float>  m_drin2_1m;
  vector<float>  m_drout1_1m;
  vector<float>  m_drout2_1m;
  vector<float>  m_t01;
  vector<float>  m_t02;
    
  vector<float>  m_z01;
  vector<float>  m_z02;
  vector<float>  m_counts1;
  vector<float>  m_counts2;
  vector<float>  m_sigmacounts1;
  vector<float>  m_sigmacounts2;
  
  vector<float>  m_1scounts1;
  vector<float>  m_1scounts2;
  vector<float>  m_1ssigmacounts1;
  vector<float>  m_1ssigmacounts2;

  vector<float>  m_1mcounts1;
  vector<float>  m_1mcounts2;
  vector<float>  m_1msigmacounts1;
  vector<float>  m_1msigmacounts2;

  ////

  vector<float>  *t_z01;
  vector<float>  *t_z02;
  vector<float>  *t_din1;
  vector<float>  *t_din2;
  vector<float>  *t_drin1;
  vector<float>  *t_drin2;
  vector<float>  *t_drout1;
  vector<float>  *t_drout2;
  vector<float>  *t_drin1_1s;
  vector<float>  *t_drin2_1s;
  vector<float>  *t_drout1_1s;
  vector<float>  *t_drout2_1s;
  vector<float>  *t_drin1_1m;
  vector<float>  *t_drin2_1m;
  vector<float>  *t_drout1_1m;
  vector<float>  *t_drout2_1m;

  TBranch *b_z01;
  TBranch *b_z02;
  TBranch *b_din1;
  TBranch *b_din2;
  TBranch *b_drin1;
  TBranch *b_drin2;
  TBranch *b_drout1;
  TBranch *b_drout2;
  TBranch *b_drin1_1s;
  TBranch *b_drin2_1s;
  TBranch *b_drout1_1s;
  TBranch *b_drout2_1s;
  TBranch *b_drin1_1m;
  TBranch *b_drin2_1m;
  TBranch *b_drout1_1m;
  TBranch *b_drout2_1m;
  
  ///Outputhistos
  //TH2D * sdose1_vs_z ;
  //TH2D * sdose2_vs_z ;

  TH2D * din1_vs_z ;//
  TH2D * din2_vs_z ;//


  TH2D * drin1_vs_z ;//
  TH2D * drin1_1s_vs_z ;//
  TH2D * drin1_1m_vs_z ;//

  TH2D * drin2_vs_z ;//
  TH2D * drin2_1s_vs_z ;//
  TH2D * drin2_1m_vs_z ;//

  TH2D * drout1_vs_z ;//
  TH2D * drout1_1s_vs_z ;//
  TH2D * drout1_1m_vs_z ;//

  TH2D * drout2_vs_z ;//
  TH2D * drout2_1s_vs_z ;//
  TH2D * drout2_1m_vs_z ;//

  TH2D * drratio1_vs_z ;//
  TH2D * drratio1_1s_vs_z ;//
  TH2D * drratio1_1m_vs_z ;//

  TH2D * drratio2_vs_z ;//
  TH2D * drratio2_1s_vs_z ;//
  TH2D * drratio2_1m_vs_z ;//

  TH2D * drsum_vs_z ;//
  TH2D * drsum_1s_vs_z ;//
  TH2D * drsum_1m_vs_z ;//

  ///Per Step
  TH1D * hdrin1 ;//
  TH1D * hdrin1_1s ;//
  TH1D * hdrin1_1m ;//

  TH1D * hdrin2 ;//
  TH1D * hdrin2_1s ;//
  TH1D * hdrin2_1m ;//

  TH1D * hdrout1 ;//
  TH1D * hdrout1_1s ;//
  TH1D * hdrout1_1m ;//

  TH1D * hdrout2 ;//
  TH1D * hdrout2_1s ;//
  TH1D * hdrout2_1m ;//
  
  TH1D * hdrin1_vs_t ;//
  TH1D * hdrin2_vs_t ;//
  TH1D * hdrout1_vs_t ;//
  TH1D * hdrout2_vs_t ;//

    
 public:
  ~DRPS_twodets();
  DRPS_twodets(char*, char*, int);
  void SetDebugLevel();
  void Initialize(int);
  void DeclarePerStepHisto(int);
  void Finalize();
  string GetDebugLevel();
  void PrintConfiguration(string);
  void Loop();
  void MakeDefaultPlots();
  void SaveHistos();
  void DrawAndSave(int);
  void Init1(TTree *myTree1){

    t_z01=0;
    t_din1=0;
    t_drin1=0;
    t_drout1=0;
    t_drin1_1s=0;
    t_drout1_1s=0;
    t_drin1_1m=0;
    t_drout1_1m=0;
    myTree1->SetBranchAddress("z01", &t_z01, &b_z01);
    myTree1->SetBranchAddress("din1", &t_din1, &b_din1);
    myTree1->SetBranchAddress("drin1", &t_drin1, &b_drin1);
    myTree1->SetBranchAddress("drout1", &t_drout1, &b_drout1);
    myTree1->SetBranchAddress("drin1_1s", &t_drin1_1s, &b_drin1_1s);
    myTree1->SetBranchAddress("drout1_1s", &t_drout1_1s, &b_drout1_1s);
    myTree1->SetBranchAddress("drin1_1m", &t_drin1_1m, &b_drin1_1m);
    myTree1->SetBranchAddress("drout1_1m", &t_drout1_1m, &b_drout1_1m);

  }

  void Init2(TTree *myTree2){

    t_z02=0;
    t_din2=0;
    t_drin2=0;
    t_drout2=0;
    t_drin2_1s=0;
    t_drout2_1s=0;
    t_drin2_1m=0;
    t_drout2_1m=0;
    myTree2->SetBranchAddress("z02", &t_z02, &b_z02);
    myTree2->SetBranchAddress("din2", &t_din2, &b_din2);
    myTree2->SetBranchAddress("drin2", &t_drin2, &b_drin2);
    myTree2->SetBranchAddress("drout2", &t_drout2, &b_drout2);
    myTree2->SetBranchAddress("drin2_1s", &t_drin2_1s, &b_drin2_1s);
    myTree2->SetBranchAddress("drout2_1s", &t_drout2_1s, &b_drout2_1s);
    myTree2->SetBranchAddress("drin2_1m", &t_drin2_1m, &b_drin2_1m);
    myTree2->SetBranchAddress("drout2_1m", &t_drout2_1m, &b_drout2_1m);
  }
  
};
#endif
