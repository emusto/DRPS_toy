#include "TH1.h"
#include "TH2.h"
#include "TFile.h"
#include "TRandom3.h"
#include "TSystem.h"
#include "TStyle.h"
#include "THttpServer.h"

Bool_t bFillHist = kTRUE;

void httpcontrol()
{
//  This program demonstrates simple application control via THttpServer
//  Two histogram are filled within endless loop.
//  Via published commands one can enable/disable histograms filling
//  There are also command to clear histograms content
//
//  After macro started, open in browser with url
//      http://localhost:8080
//
//  Histograms will be automatically displayed and
//  monitoring with interval 2000 ms started
  gStyle->ToggleEventStatus();
  TFile *fin=TFile::Open("test_step0.root"); 
  TH1D *step0_drin1 = (TH1D*)fin->Get("step0_drin1");
  Int_t numargs = 0;  
   // start http server
   THttpServer* serv = new THttpServer("http:8080");

   // One could specify location of newer version of JSROOT
   // serv->SetJSROOT("https://root.cern.ch/js/3.5/");
   // serv->SetJSROOT("http://web-docs.gsi.de/~linev/js/3.5/");

   // register histograms
   serv->Register("/",step0_drin1);


   // enable monitoring and
   // specify items to draw when page is opened
   // serv->SetItemField("/","_monitoring","2000");
   serv->SetItemField("/","_numargs", TString::Format("%d", numargs));
   serv->SetItemField("/","_drawitem","step0_drin1");
   serv->SetItemField("/","_drawopt","all");

   // register simple start/stop commands
   serv->RegisterCommand("/Start", "bFillHist=kTRUE;", "button;rootsys/icons/ed_execute.png");
   serv->RegisterCommand("/Stop",  "bFillHist=kFALSE;", "button;rootsys/icons/ed_interrupt.png");
   // serv->RegisterCommand("/Integrate between first bin and","/step0_drin1/->Integral(0,%arg1%);", "button;rootsys/icons/ed_execute.png");

   serv->RegisterCommand("/Rebin","/step0_drin1/->Rebin(%arg1%);", "button;rootsys/icons/ed_execute.png");
   serv->SetItemField("/Rebin","_update_item", "step0_drin1"); // let browser update histogram view after commands execution

   //   serv->SetItemField("/RebinHPX","_update_item", "hpx"); // let browser update histogram view after commands execution
   // one could hide commands and let them appear only as buttons
   serv->Hide("/Start");
   serv->Hide("/Stop");

   // register commands, invoking object methods
   serv->RegisterCommand("/ResetColor","/step0_drin1/->SetLineColor(2)", "button;rootsys/icons/ed_delete.png");
   serv->RegisterCommand("/Integral","/step0_drin1/->Integral()", "button;rootsys/icons/ed_delete.png");





   // create debug text element, use MathJax - works only on Firefox
   serv->CreateItem("/Debug","debug output");
   serv->SetItemField("/Debug", "_kind", "Text");
   serv->SetItemField("/Debug", "value","\\(\\displaystyle{x+1\\over y-1}\\)");
   serv->SetItemField("/Debug", "mathjax", "true");


}
