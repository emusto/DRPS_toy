


#include "DRPS_twodets.h"

/*as input parameter we can set the Dose of the source and its the uncertainty,the source position, the source frequency, 
 the detectors position(x,r), the detector sensitivity, the integration time*/

/*
Models used:
- Uniform Dose rate of the source, gaussian incertainty;
- Poisson number of counts of the detector
*/


DRPS_twodets::DRPS_twodets(char * input, char * output, int nzsteps):
  m_parser(input),
  m_output(output),
  m_nzsteps(nzsteps),
  m_logger("DRPS_twodets")

{
  m_options=m_parser.ParseConfiguration();
  m_debuglevel=GetDebugLevel();
  SetDebugLevel();
  CreateOutput();
}

DRPS_twodets::~DRPS_twodets()
{
}

string DRPS_twodets::GetDebugLevel(){

  string outputLevelString="INFO";//default
  auto mapiter=m_options.find("DEBUGLEVEL");
  if(mapiter!=m_options.end())outputLevelString=mapiter->second;
  return outputLevelString;
  
}
void DRPS_twodets::SetDebugLevel()
  
{

  MessageType type = INFO;
  if( m_debuglevel == "DEBUG" )   type = DEBUG;
  else if( m_debuglevel == "INFO" )    type = INFO;
  else if( m_debuglevel == "WARNING" ) type = WARNING;
  else if( m_debuglevel == "ERROR" )   type = ERROR;
  else if( m_debuglevel == "FATAL" )   type = FATAL;

  LoggerWriter::Instance()->SetMinType( type );
}

void DRPS_twodets::Initialize(int nstep)
{
  PrintConfiguration(m_debuglevel);
  SetupDetectors();
  SetupSource(nstep);
  DeclarePerStepHisto(nstep);

}
void DRPS_twodets::SaveHistos()
{
  outputHistosFile->Write();
  outputHistosFile->Close();

}


void DRPS_twodets::PrintConfiguration(string dl)
{
  m_logger<<DEBUG<<">---------Printing configuration parameters-----------<" <<Logger::endmsg;
  if(dl == "DEBUG"){
    
    for(auto it = m_options.cbegin();
	it != m_options.cend(); ++it)
      {
	m_logger<<DEBUG<< it->first << " : " << it->second <<Logger::endmsg;
      }

  }
  m_logger<<DEBUG<<">-----------------------------------------------------<" <<Logger::endmsg;
}

void DRPS_twodets::SetupDetectors()
{
  //  auto mapiter;

  float d1sensitivity = 0.15;
  auto mapiter=m_options.find("D1SENSITIVITY");
  if(mapiter!=m_options.end())d1sensitivity = stof (mapiter->second);

  float d2sensitivity = 0.15;
  mapiter=m_options.find("D2SENSITIVITY");
  if(mapiter!=m_options.end())d2sensitivity = stof (mapiter->second);
    

  float d1integrationtime = 0.05;
  mapiter=m_options.find("D1INTEGRATIONTIME");
  if(mapiter!=m_options.end())d1integrationtime = stof (mapiter->second);
    

  float d2integrationtime = 0.05;
  mapiter=m_options.find("D2INTEGRATIONTIME");
  if(mapiter!=m_options.end())d2integrationtime = stof (mapiter->second);
    
  float d1yposition = 0.;
  mapiter=m_options.find("D1YPOSITION");
  if(mapiter!=m_options.end()) d1yposition = stof (mapiter->second);

  float d2yposition = 0.;
  mapiter=m_options.find("D2YPOSITION");
  if(mapiter!=m_options.end()) d2yposition = stof (mapiter->second);

  float d1zposition = 0.;
  mapiter=m_options.find("D1ZPOSITION");
  if(mapiter!=m_options.end()) d1zposition = stof (mapiter->second);

  float d2zposition = 0.;
  mapiter=m_options.find("D2ZPOSITION");
  if(mapiter!=m_options.end()) d2zposition = stof (mapiter->second);

  float d1nuisance =0.; 
  mapiter=m_options.find("D1NUISANCE");
  if(mapiter!=m_options.end()) d1nuisance = stof (mapiter->second);

  float d2nuisance =0.; 
  mapiter=m_options.find("D2NUISANCE");
  if(mapiter!=m_options.end()) d2nuisance = stof (mapiter->second);
  
  m_o1=new OutsideDetector(d1sensitivity,d1integrationtime, d1yposition, d1zposition,d1nuisance, m_id1);
  m_o2=new OutsideDetector(d2sensitivity,d2integrationtime, d2yposition, d2zposition, d2nuisance, m_id2);
  m_logger<<DEBUG<<"Detectors initialized" <<Logger::endmsg;
}

void DRPS_twodets::SetupSource(int nstep)
{
  double sdose = 5.;
  double sdoseuncertainty = 0.;
  double sfrequency = 100.;
  bool sisrandom = true;
  double sminz=0.;
  double smaxz=200.;

  auto mapiter=m_options.find("SOURCEDOSE");
  if(mapiter!=m_options.end())sdose = stof(mapiter->second);

  mapiter=m_options.find("SOURCEDOSEUNCERTAINTY");
  if(mapiter!=m_options.end())sdoseuncertainty = stof(mapiter->second);

  mapiter=m_options.find("SOURCEFREQUENCY");
  if(mapiter!=m_options.end())sfrequency = stof(mapiter->second);
  
  mapiter=m_options.find("SOURCEMINZ");
  if(mapiter!=m_options.end())sminz = stof(mapiter->second);
  
  mapiter=m_options.find("SOURCEMAXZ");
  if(mapiter!=m_options.end())smaxz = stof(mapiter->second);
  
  mapiter=m_options.find("SOURCEISRANDOM");
  if(mapiter!=m_options.end()){
    if(mapiter->second!="true") sisrandom = false;
  }
  if(m_nzsteps>1){

    float stepsize = (smaxz - sminz)/m_nzsteps;

    m_s = new Source(sdose,sdoseuncertainty, sfrequency, false,sminz+nstep*stepsize ,sminz+nstep*stepsize );
  }else{
    m_s = new Source(sdose,sdoseuncertainty, sfrequency, sisrandom, sminz, smaxz);
  }

  m_logger<<DEBUG<<"Source initialized" <<Logger::endmsg;
}


void DRPS_twodets::DeclarePerStepHisto(int nstep)
{

  float maxdose=0.;
  auto  mapiter=m_options.find("SOURCEDOSE");
  if(mapiter!=m_options.end())maxdose = stof(mapiter->second);

  int acquisitiontime=600; //s == 10 minutes of acquisition
  mapiter=m_options.find("ACQUISITIONTIME");
  if( mapiter!=m_options.end()) acquisitiontime = stoi (mapiter->second);
  
  string prefix="step"+to_string(nstep);
  string suffix=prefix;
  string filename(m_output);
  filename = "rootfiles/"+filename+"_"+suffix+".root";
  outputHistosFile = new TFile(filename.c_str(),"RECREATE");

  string sdrin1=prefix+"_drin1" ;//
  string sdrin1_1s=prefix+"_drin1_1s"  ;//
  string sdrin1_1m=prefix+"_drin1_1m"  ;//

  string sdrin2=prefix+"_drin2"  ;//
  string sdrin2_1s=prefix+"_drin2_1s"  ;//
  string sdrin2_1m=prefix+"_drin2_1m"  ;//

  string sdrout1=prefix+"_drout1"  ;//
  string sdrout1_1s=prefix+"_drout1_1s" ;//
  string sdrout1_1m=prefix+"_drout1_1m" ;//

  string sdrout2=prefix+"_drout2" ;//
  string sdrout2_1s=prefix+"_drout2_1s" ;//
  string sdrout2_1m=prefix+"_drout2_1m" ;//

  
  string sdrin1_vs_t=prefix+"_drin1_vs_t" ;//
  string sdrin2_vs_t=prefix+"_drin2_vs_t" ;//
  string sdrout1_vs_t=prefix+"_drout1_vs_t" ;//
  string sdrout2_vs_t=prefix+"_drout2_vs_t" ;//

  float maxdr=maxdose*0.7;
  float mindr = maxdr/6;
  
  hdrin1 = new TH1D (sdrin1.c_str(),"Internal dose rate, Detector 1 (z=0 cm)",100,mindr*2E5,maxdr*2E5);
  hdrin1->SetLineColor(1);
  hdrin1->SetMarkerColor(1);
  hdrin1->GetXaxis()->SetTitle("Dose rate (#muSv/h)");
  
  hdrin1_1s = new TH1D (sdrin1_1s.c_str(),"Internal dose rate, Detector 1 (z=0 cm), 1s avg",100,mindr*2E5,maxdr*2E5);    
  hdrin1_1s->SetLineColor(1);
  hdrin1_1s->SetMarkerColor(1);
  hdrin1_1s->GetXaxis()->SetTitle("Dose rate (#muSv/h)");

  hdrin1_1m = new TH1D (sdrin1_1m.c_str(),"Internal dose rate, Detector 1 (z=0 cm), 1m avg",100,mindr*2E5,maxdr*2E5);
  hdrin1_1m->SetLineColor(1);
  hdrin1_1m->SetMarkerColor(1);
  hdrin1_1m->GetXaxis()->SetTitle("Dose rate (#muSv/h)");
  
  hdrin2 = new TH1D (sdrin2.c_str(),"Internal dose rate, Detector 2 (z=200 cm)",100,mindr*2E5,maxdr*2E5);
  hdrin2->SetLineColor(2);
  hdrin2->SetMarkerColor(2);
  hdrin2->GetXaxis()->SetTitle("Dose rate (#muSv/h)");
  
  hdrin2_1s = new TH1D (sdrin2_1s.c_str(),"Internal dose rate, Detector 2 (z=200 cm), 1s avg",100,mindr*2E5,maxdr*2E5);         
  hdrin2_1s->SetLineColor(2);
  hdrin2_1s->SetMarkerColor(2);
  hdrin2_1s->GetXaxis()->SetTitle("Dose rate (#muSv/h)");

  hdrin2_1m = new TH1D (sdrin2_1m.c_str(),"Internal dose rate, Detector 2 (z=200 cm), 1m avg",100,mindr*2E5,maxdr*2E5);
  hdrin2_1m->SetLineColor(2);
  hdrin2_1m->SetMarkerColor(2);
  hdrin2_1m->GetXaxis()->SetTitle("Dose rate (#muSv/h)");
  
  hdrout1 = new TH1D (sdrout1.c_str(),"Outside dose rate, Detector 1 (z=0 cm)",100,mindr,maxdr*3);
  hdrout1->SetLineColor(1);
  hdrout1->SetMarkerColor(1);
  hdrout1->GetXaxis()->SetTitle("Dose rate (#muSv/h)");
  
  hdrout1_1s = new TH1D (sdrout1_1s.c_str(),"Outside dose rate, Detector 1 (z=0 cm), 1s avg",100,mindr,maxdr*3);
  hdrout1_1s->SetLineColor(1);
  hdrout1_1s->SetMarkerColor(1);
  hdrout1_1s->GetXaxis()->SetTitle("Dose rate (#muSv/h)");

  hdrout1_1m = new TH1D (sdrout1_1m.c_str(),"Outside dose rate, Detector 1 (z=0 cm), 1m avg",100,mindr,maxdr*3);
  hdrout1_1m->SetLineColor(1);
  hdrout1_1m->SetMarkerColor(1);
  hdrout1_1m->GetXaxis()->SetTitle("Dose rate (#muSv/h)");
  
  hdrout2 = new TH1D (sdrout2.c_str(),"Outside dose rate, Detector 2 (z=200 cm)",100,mindr,maxdr*3);    	                
  hdrout2->SetLineColor(2);
  hdrout2->SetMarkerColor(2);
  hdrout2->GetXaxis()->SetTitle("Dose rate (#muSv/h)");
  
  hdrout2_1s = new TH1D (sdrout2_1s.c_str(),"Outside dose rate, Detector 2 (z=200 cm), 1s avg",100,mindr,maxdr*3);    	      
  hdrout2_1s->SetLineColor(2);
  hdrout2_1s->SetMarkerColor(2);
  hdrout2_1s->GetXaxis()->SetTitle("Dose rate (#muSv/h)");
  
  hdrout2_1m = new TH1D (sdrout2_1m.c_str(),"Outside dose rate, Detector 2 (z=200 cm), 1m avg",100,mindr,maxdr*3);      
  hdrout2_1m->SetLineColor(2);
  hdrout2_1m->SetMarkerColor(2);
  hdrout2_1m->GetXaxis()->SetTitle("Dose rate (#muSv/h)");  
  
  hdrin1_vs_t = new TH1D (sdrin1_vs_t.c_str(), "Internal dose rate vs time, Detector 1 (z=0 cm)",acquisitiontime+1,0,acquisitiontime+1);//100,mindr*2E5,maxdr*2E5);  
  hdrin1_vs_t->SetLineColor(1);
  hdrin1_vs_t->SetMarkerColor(1);
  hdrin1_vs_t->GetYaxis()->SetTitle("Dose rate (#muSv/h)");
  hdrin1_vs_t->GetXaxis()->SetTitle("Acquisition time (s)");  
  
  hdrin2_vs_t = new TH1D (sdrin2_vs_t.c_str(),"Internal dose rate vs time, Detector 2 (z=200 cm)",acquisitiontime+1,0,acquisitiontime+1);//,100,mindr*2E5,maxdr*2E5);  
  hdrin2_vs_t->SetLineColor(2);
  hdrin2_vs_t->SetMarkerColor(2);
  hdrin2_vs_t->GetYaxis()->SetTitle("Dose rate (#muSv/h)");
  hdrin2_vs_t->GetXaxis()->SetTitle("Acquisition time (s)");
  
  hdrout1_vs_t = new TH1D (sdrout1_vs_t.c_str(),"Outside dose rate vs time, Detector 1 (z=0 cm)",acquisitiontime+1,0,acquisitiontime+1);//,100,mindr,maxdr*3);  
  hdrout1_vs_t->SetLineColor(1);
  hdrout1_vs_t->SetMarkerColor(1);
  hdrout1_vs_t->GetYaxis()->SetTitle("Dose rate (#muSv/h)");
  hdrout1_vs_t->GetXaxis()->SetTitle("Acquisition time (s)");
  
  hdrout2_vs_t = new TH1D (sdrout2_vs_t.c_str(),"Outside dose rate vs time, Detector 2 (z=200 cm)",acquisitiontime+1,0,acquisitiontime+1);//,100,mindr,maxdr*3);    
  hdrout2_vs_t->SetLineColor(2);
  hdrout2_vs_t->SetMarkerColor(2);
  hdrout2_vs_t->GetYaxis()->SetTitle("Dose rate (#muSv/h)");
  hdrout2_vs_t->GetXaxis()->SetTitle("Acquisition time (s)");
  
  m_logger<<DEBUG<<"Per Step Histos initialized" <<Logger::endmsg;
}

void DRPS_twodets::CreateOutput()
{
  m_id1 = "OutDetector1";
  auto mapiter=m_options.find("D1ID");
  if(mapiter!=m_options.end())m_id1 = mapiter->second;

  m_id2 = "OutDetector2";
  mapiter=m_options.find("D2ID");
  if(mapiter!=m_options.end())m_id2 = mapiter->second;
  string rootfile="rootfiles/"+string(m_output)+".root";
  
  m_f = new TFile(rootfile.c_str(),"RECREATE");

  OD1tree = new TTree(m_id1.c_str(),m_id1.c_str());
  OD1tree->Branch("t01", &m_t01);
  OD1tree->Branch("z01", &m_z01);
  OD1tree->Branch("d01", &m_d01);
  OD1tree->Branch("din1", &m_din1);
  OD1tree->Branch("counts1", &m_counts1);
  OD1tree->Branch("sigmacounts1", &m_sigmacounts1);
  OD1tree->Branch("1s_counts1", &m_1scounts1);
  OD1tree->Branch("sigma_1s_counts1", &m_1ssigmacounts1);
  OD1tree->Branch("1m_counts1", &m_1mcounts1);
  OD1tree->Branch("sigma_1m_counts1", &m_1msigmacounts1);
  OD1tree->Branch("drin1", &m_drin1);
  OD1tree->Branch("drout1", &m_drout1);
  OD1tree->Branch("drin1_1s", &m_drin1_1s);
  OD1tree->Branch("drout1_1s", &m_drout1_1s);
  OD1tree->Branch("drin1_1m", &m_drin1_1m);
  OD1tree->Branch("drout1_1m", &m_drout1_1m);

  
  OD2tree = new TTree(m_id2.c_str(),m_id2.c_str());
  OD2tree->Branch("t02", &m_t02);
  OD2tree->Branch("d02", &m_d02);
  OD2tree->Branch("z02", &m_z02);
  OD2tree->Branch("din2", &m_din2);
  OD2tree->Branch("counts2", &m_counts2);
  OD2tree->Branch("sigmacounts2", &m_sigmacounts2);
  OD2tree->Branch("1s_counts2", &m_1scounts2);
  OD2tree->Branch("sigma_1s_counts2", &m_1ssigmacounts2);
  OD2tree->Branch("1m_counts2", &m_1mcounts2);
  OD2tree->Branch("sigma_1m_counts2", &m_1msigmacounts2);
  OD2tree->Branch("drin2", &m_drin2);
  OD2tree->Branch("drout2", &m_drout2);
  OD2tree->Branch("drin2_1s", &m_drin2_1s);
  OD2tree->Branch("drout2_1s", &m_drout2_1s);
  OD2tree->Branch("drin2_1m", &m_drin2_1m);
  OD2tree->Branch("drout2_1m", &m_drout2_1m);

 
  m_logger<<DEBUG<<"Output Trees initialized" <<Logger::endmsg;
}

void DRPS_twodets::Finalize(){

  m_logger<<INFO<<"Done!"<<Logger::endmsg;
  m_f->Write();
  m_f->Close();
  MakeDefaultPlots();
}

void DRPS_twodets::Loop()
{
  m_d01.clear();
  m_d02.clear();
  m_din1.clear();
  m_din2.clear();
  m_drin1.clear();
  m_drin2.clear();
  m_drout1.clear();
  m_drout2.clear();
  m_drin1_1s.clear();
  m_drin2_1s.clear();
  m_drout1_1s.clear();
  m_drout2_1s.clear();
  m_drin1_1m.clear();
  m_drin2_1m.clear();
  m_drout1_1m.clear();
  m_drout2_1m.clear();
  m_t01.clear();
  m_t02.clear();
 
  m_z01.clear();
  m_z02.clear();
  m_counts1.clear();
  m_counts2.clear();
  m_sigmacounts1.clear();
  m_sigmacounts2.clear();
 
  m_1scounts1.clear();
  m_1scounts2.clear();
  m_1ssigmacounts1.clear();
  m_1ssigmacounts2.clear();

  m_1mcounts1.clear();
  m_1mcounts2.clear();
  m_1msigmacounts1.clear();
  m_1msigmacounts2.clear();

  float z_source= m_s->Getz();

  float timing=0.01;
  m_logger<<INFO<<"Source coordinate is: "<<z_source<<Logger::endmsg;
  int acquisitiontime=600; //s == 10 minutes of acquisition

  auto mapiter=m_options.find("ACQUISITIONTIME");
  if( mapiter!=m_options.end()) acquisitiontime = stoi (mapiter->second);
 
  float nsample1=m_s->GetFrequency()*m_o1->GetIntegrationtime();
  float nsample2=m_s->GetFrequency()*m_o2->GetIntegrationtime();

  int avg1s_nsample1=int(1./m_o1->GetIntegrationtime());
  int avg1s_nsample2=int(1./m_o2->GetIntegrationtime());

  int avg1m_nsample1=int(60./m_o1->GetIntegrationtime());
  int avg1m_nsample2=int(60./m_o2->GetIntegrationtime());

  int ntoy=acquisitiontime*m_s->GetFrequency();

  int counter1=0;
  int counter2=0;

  int counter1_1s=0;
  int counter2_1s=0;

  int counter1_1m=0;
  int counter2_1m=0;
  
  float integratedd1=0.;
  float integratedd2=0.;
  float extracted_dr=0.;

  float dosedet1=0.;
  float dosedet2=0.;

  float idosedet1=0.;
  float idosedet2=0.;

  float contdets1=0.;
  float contdets2=0.;
  float sigmacdet2=0.;
  float sigmacdet1=0.;

  float avgcounts_1s1=0.;
  float avgcounts_1s2=0.;

  float avgcounts_1m1=0.;
  float avgcounts_1m2=0.;

  float sigmacounts_1s1=0.;
  float sigmacounts_1s2=0.;

  float sigmacounts_1m1=0.;
  float sigmacounts_1m2=0.;

  float drin1=0.;
  float drin2=0.;

  float drout1=0.;
  float drout2=0.;

  float avgdrin1_1s=0.;
  float avgdrout1_1s=0.;

  float avgdrin2_1s=0.;
  float avgdrout2_1s=0.;

  float avgdrin1_1m=0.;
  float avgdrout1_1m=0.;

  float avgdrin2_1m=0.;
  float avgdrout2_1m=0.;
  const float default_val=-999.;
  
  m_logger<<DEBUG<<"ntoys: "<<ntoy<<Logger::endmsg;
  m_logger<<DEBUG<<"nsample1: "<<nsample1<<Logger::endmsg;
  m_logger<<DEBUG<<"nsample2: "<<nsample2<<Logger::endmsg;

  for (int i_toy=0; i_toy<ntoy; i_toy++){
    
    counter1++;
    counter2++;
    extracted_dr= m_s->GetSmearedDose();

    
    if(counter1<nsample1){
      
      integratedd1 +=extracted_dr; 
      
    }else{
      
      idosedet1=m_o1->idose(integratedd1,z_source);
      contdets1=m_o1->ncounts(idosedet1);
      sigmacdet1=m_o1->ncounts_rel_err(contdets1)/nsample1;//rel error on # of counts per burst
      contdets1=contdets1/nsample1;//average counts per burst
      m_logger<<DEBUG<<"countsdet1: "<<contdets1<<Logger::endmsg;
      dosedet1=m_o1->idmeasureddose(contdets1,sigmacdet1);
      drin1=dosedet1*3.6*1E5; //muSv/h ---shall we do perPulse??
      drout1=m_o1->measureddose(dosedet1*3.6*1E5,z_source);

      m_d01.push_back(extracted_dr);
      m_z01.push_back(z_source);
      m_t01.push_back(timing);
      m_din1.push_back(idosedet1/nsample1);      
      m_counts1.push_back(contdets1);
      m_sigmacounts1.push_back(sigmacdet1);

      m_drin1.push_back(drin1);
      m_drout1.push_back(drout1);

      hdrin1->Fill(drin1);
      hdrout1->Fill(drout1);

      hdrin1_vs_t->SetBinContent(timing,drin1);
      hdrout1_vs_t->SetBinContent(timing,drout1);

      if(counter1_1s<avg1s_nsample1){
	counter1_1s++;
	avgcounts_1s1+=contdets1;
	sigmacounts_1s1+=sigmacdet1;
	avgdrin1_1s+=drin1;
	avgdrout1_1s+=drout1;
	m_1scounts1.push_back(default_val); 
	m_1ssigmacounts1.push_back(default_val); 
	m_drin1_1s.push_back(default_val); 
	m_drout1_1s.push_back(default_val); 

	
      }else{
	avgcounts_1s1=avgcounts_1s1/avg1s_nsample1;
	sigmacounts_1s1=sigmacounts_1s1/avg1s_nsample1;
	avgdrin1_1s=avgdrin1_1s/avg1s_nsample1;
	avgdrout1_1s=avgdrout1_1s/avg1s_nsample1;

	m_1scounts1.push_back(avgcounts_1s1); 
	m_1ssigmacounts1.push_back(sigmacounts_1s1); 
	m_drin1_1s.push_back(avgdrin1_1s); 
	m_drout1_1s.push_back(avgdrout1_1s); 

	hdrin1_1s->Fill(avgdrin1_1s);
	hdrout1_1s->Fill(avgdrout1_1s);
	counter1_1s=0;
	avgcounts_1s1=0.;
	sigmacounts_1s1=0.;
	avgdrin1_1s=0.;
	avgdrout1_1s=0.;

      }

      if(counter1_1m<avg1m_nsample1){
	counter1_1m++;
	avgcounts_1m1+=contdets1;
	sigmacounts_1m1+=sigmacdet1;
	avgdrin1_1m+=drin1;
	avgdrout1_1m+=drout1;
	m_1mcounts1.push_back(default_val); 
	m_1msigmacounts1.push_back(default_val); 
	m_drin1_1m.push_back(default_val); 
	m_drout1_1m.push_back(default_val); 

      }else{
	avgcounts_1m1=avgcounts_1m1/avg1m_nsample1;
	sigmacounts_1m1=sigmacounts_1m1/avg1m_nsample1;
	avgdrin1_1m=avgdrin1_1m/avg1m_nsample1;
	avgdrout1_1m=avgdrout1_1m/avg1m_nsample1;

	m_1mcounts1.push_back(avgcounts_1m1); 
	m_1msigmacounts1.push_back(sigmacounts_1m1); 
	m_drin1_1m.push_back(avgdrin1_1m); 
	m_drout1_1m.push_back(avgdrout1_1m); 

	hdrin1_1m->Fill(avgdrin1_1m);
	hdrout1_1m->Fill(avgdrout1_1m);
	
	counter1_1m=0;
	avgcounts_1m1=0.;
	sigmacounts_1m1=0.;
	avgdrin1_1m=0.;
	avgdrout1_1m=0.;
      }

      counter1=0;

      integratedd1=0.;
      //      OD1tree->Fill();
     
    }
  
    if(counter2<nsample2){
      
      integratedd2 +=extracted_dr; 
      
    }else{

      idosedet2=m_o2->idose(integratedd2,z_source);
      contdets2=m_o2->ncounts(idosedet2);
      sigmacdet2=m_o2->ncounts_rel_err(contdets2)/nsample2;//rel error on # of counts per burst
      contdets2=contdets2/nsample2;//average counts per burst
      m_logger<<DEBUG<<"countsdet2: "<<contdets2<<Logger::endmsg;


      dosedet2=m_o2->idmeasureddose(contdets2,sigmacdet2);
      drin2=dosedet2*3.6*1E5; //muSv/h ---shall we do perPulse??

      drout2=m_o2->measureddose(dosedet2*3.6*1E5,z_source);

      m_d02.push_back(extracted_dr);
      m_z02.push_back(z_source);
      m_t02.push_back(timing);
      m_din2.push_back(idosedet2/nsample2);      
      m_counts2.push_back(contdets2);
      m_sigmacounts2.push_back(sigmacdet2);

      m_drin2.push_back(drin2);
      m_drout2.push_back(drout2);
      
      hdrin2->Fill(drin2);
      hdrout2->Fill(drout2);

      hdrin2_vs_t->SetBinContent(timing,drin2);
      hdrout2_vs_t->SetBinContent(timing,drout2);

      if(counter2_1s<avg1s_nsample2){
	counter2_1s++;
	avgcounts_1s2+=contdets2;
	sigmacounts_1s2+=sigmacdet2;
	avgdrin2_1s+=drin2;
	avgdrout2_1s+=drout2;

	m_1scounts2.push_back(default_val); 
	m_1ssigmacounts2.push_back(default_val); 
	m_drin2_1s.push_back(default_val); 
	m_drout2_1s.push_back(default_val); 
	
      }else{
	avgcounts_1s2=avgcounts_1s2/avg1s_nsample2;
	sigmacounts_1s2=sigmacounts_1s2/avg1s_nsample2;
	avgdrin2_1s=avgdrin2_1s/avg1s_nsample2;
	avgdrout2_1s=avgdrout2_1s/avg1s_nsample2;

	m_1scounts2.push_back(avgcounts_1s2); 
	m_1ssigmacounts2.push_back(sigmacounts_1s2); 
	m_drin2_1s.push_back(avgdrin2_1s); 
	m_drout2_1s.push_back(avgdrout2_1s); 

	hdrin2_1s->Fill(avgdrin2_1s);
	hdrout2_1s->Fill(avgdrout2_1s);
	
	counter2_1s=0;
	avgcounts_1s2=0.;
	sigmacounts_1s2=0.;
	avgdrin2_1s=0.;
	avgdrout2_1s=0.;
      }

      if(counter2_1m<avg1m_nsample2){
	counter2_1m++;
	avgcounts_1m2+=contdets2;
	sigmacounts_1m2+=sigmacdet2;
	avgdrin2_1m+=drin2;
	avgdrout2_1m+=drout2;

	m_1mcounts2.push_back(default_val); 
	m_1msigmacounts2.push_back(default_val); 
	m_drin2_1m.push_back(default_val); 
	m_drout2_1m.push_back(default_val); 
	
      }else{
	avgcounts_1m2=avgcounts_1m2/avg1m_nsample2;
	sigmacounts_1m2=sigmacounts_1m2/avg1m_nsample2;
	avgdrin2_1m=avgdrin2_1m/avg1m_nsample2;
	avgdrout2_1m=avgdrout2_1m/avg1m_nsample2;

	m_1mcounts2.push_back(avgcounts_1m2); 
	m_1msigmacounts2.push_back(sigmacounts_1m2); 
	m_drin2_1m.push_back(avgdrin2_1m); 
	m_drout2_1m.push_back(avgdrout2_1m); 

	hdrin2_1m->Fill(avgdrin2_1m);
	hdrout2_1m->Fill(avgdrout2_1m);
	
	counter2_1m=0;
	avgcounts_1m2=0.;
	sigmacounts_1m2=0.;
	avgdrin2_1m=0.;
	avgdrout2_1m=0.;
	
      }
      counter2=0;
      integratedd2=0.;
      
    }
    timing+=0.01;       
  }
  OD1tree->Fill();
  OD2tree->Fill();

}

void DRPS_twodets::DrawAndSave(int nstep)
{

  string prefix="psfiles/Plots_Step"+to_string(nstep);

  TString psfilename = prefix+"_"+string(m_output)+".eps";
    
  TCanvas * stepcanvas = new TCanvas();
  hdrin1->Draw();
  stepcanvas->SaveAs(psfilename+"(");
  stepcanvas = new TCanvas();
  hdrin1_1s->Draw();
  stepcanvas->SaveAs(psfilename);
  stepcanvas = new TCanvas();
  hdrin1_1m->Draw();
  stepcanvas->SaveAs(psfilename);
  stepcanvas = new TCanvas();
  hdrin2->Draw();
  stepcanvas->SaveAs(psfilename);
  stepcanvas = new TCanvas();
  hdrin2_1s->Draw();
  stepcanvas->SaveAs(psfilename);
  stepcanvas = new TCanvas();
  hdrin2_1m->Draw();
  stepcanvas->SaveAs(psfilename);
  stepcanvas = new TCanvas();
  hdrout1->Draw();
  stepcanvas->SaveAs(psfilename);
  stepcanvas = new TCanvas();
  hdrout1_1s->Draw();
  stepcanvas->SaveAs(psfilename);
  stepcanvas = new TCanvas();
  hdrout1_1m->Draw();
  stepcanvas->SaveAs(psfilename);
  stepcanvas = new TCanvas();
  hdrout2->Draw();
  stepcanvas->SaveAs(psfilename);
  stepcanvas = new TCanvas();
  hdrout2_1s->Draw();
  stepcanvas->SaveAs(psfilename);
  stepcanvas = new TCanvas();
  hdrout2_1m->Draw();
  stepcanvas->SaveAs(psfilename);
  stepcanvas = new TCanvas();
  hdrin1_vs_t->Draw("col");
  stepcanvas->SaveAs(psfilename);
  stepcanvas = new TCanvas();
  hdrin2_vs_t->Draw("col");
  stepcanvas->SaveAs(psfilename);
  stepcanvas = new TCanvas();
  hdrout1_vs_t->Draw("col");
  stepcanvas->SaveAs(psfilename);
  stepcanvas = new TCanvas();
  hdrout2_vs_t->Draw("col");
  stepcanvas->SaveAs(psfilename+")");

  

}


void DRPS_twodets::MakeDefaultPlots()
{
  m_logger<<DEBUG<<"Filling global Histos" <<Logger::endmsg;
  string rootfilename="rootfiles/"+string(m_output)+".root";
  TFile myFile(rootfilename.c_str());
  TTree* myTree1 = (TTree*) myFile.Get(m_id1.c_str());
  TTree* myTree2 = (TTree*) myFile.Get(m_id2.c_str()); 

  TCanvas *c1 = new TCanvas();
  

  //  cout<<"Found max "<<*maxdin1<<endl;

  int nEntries1 = myTree1->GetEntries(); // Get the number of entries in this tree
  int nEntries2 = myTree2->GetEntries(); // Get the number of entries in this tree
  cout<<"Found tree 1"<<m_id1.c_str()<<" having entries: "<<nEntries1<<endl;
  cout<<"Found tree 1"<<m_id2.c_str()<<" having entries: "<<nEntries2<<endl;
  Init1(myTree1);
  Init2(myTree2);
  // Loop over all entries in the tree
  bool sisrandom=false;
  auto  mapiter=m_options.find("SOURCEISRANDOM");
  if(mapiter!=m_options.end()){
    if(mapiter->second!="true") sisrandom = false;
  }
  
  if (!sisrandom && m_nzsteps>1){
  float sminz=0.;
  float smaxz=0.;
  
  mapiter=m_options.find("SOURCEMINZ");
  if(mapiter!=m_options.end())sminz = stof(mapiter->second);
  
  mapiter=m_options.find("SOURCEMAXZ");
  if(mapiter!=m_options.end())smaxz = stof(mapiter->second);
  
  //  int nzbins = m_nzsteps+1;
  //  float binsize = (smaxz - sminz)/nzbins;

  float maxdose=0.;
  mapiter=m_options.find("SOURCEDOSE");
  if(mapiter!=m_options.end())maxdose = stof(mapiter->second);
  
  din1_vs_z = new TH2D("din1_vs_z","Internal Dose, 2m distance",int(smaxz)+1, sminz,smaxz+1, 100,0.,maxdose/2);
  din2_vs_z = new TH2D("din2_vs_z","Internal Dose, 2m distance",int(smaxz)+1, sminz,smaxz+1, 100,0.,maxdose/2);
  
  drin1_vs_z = new TH2D("drin1_vs_z","Internal Dose Rate, 2m distance ",int(smaxz)+1, sminz,smaxz+1, 100,0 ,maxdose*2E5);
  drin2_vs_z = new TH2D("drin2_vs_z","Internal Dose Rate, 2m distance",int(smaxz)+1, sminz,smaxz+1, 100,0 ,maxdose*2E5);
  drout1_vs_z = new TH2D("drout1_vs_z","Outside Dose Rate",int(smaxz)+1, sminz,smaxz+1, 100,0 ,maxdose*3);
  drout2_vs_z = new TH2D("drout2_vs_z","Outside Dose Rate",int(smaxz)+1, sminz,smaxz+1, 100,0 ,maxdose*3);
  drsum_vs_z = new TH2D("drsum_vs_z","Outside Dose Rate sum, Detector1+2",int(smaxz)+1, sminz,smaxz+1, 100,0 ,maxdose*3);
  drratio1_vs_z = new TH2D("drratio1_vs_z","Outside/Internal Dose Rate ratio",int(smaxz)+1, sminz,smaxz+1, 100,0 ,2E-5);
  drratio2_vs_z = new TH2D("drratio2_vs_z","Outside/Internal Dose Rate ratio",int(smaxz)+1, sminz,smaxz+1, 100,0 ,2E-5);  

  drin1_1s_vs_z = new TH2D("drin1_1s_vs_z","Internal Dose Rate, 1s avg, 2m distance",int(smaxz)+1, sminz,smaxz+1, 100,0 ,maxdose*2E5);
  drin2_1s_vs_z = new TH2D("drin2_1s_vs_z","Internal Dose Rate, 1s avg, 2m distance",int(smaxz)+1, sminz,smaxz+1, 100,0 ,maxdose*2E5);
  drout1_1s_vs_z = new TH2D("drout1_1s_vs_z","Outside Dose Rate, 1s avg, 2m distance",int(smaxz)+1, sminz,smaxz+1, 100,0 ,maxdose*3);
  drout2_1s_vs_z = new TH2D("drout2_1s_vs_z","Outside Dose Rate, 1s avg, 2m distance",int(smaxz)+1, sminz,smaxz+1, 100,0 ,maxdose*3);

  drsum_1s_vs_z = new TH2D("drsum_1s_vs_z","Dose Rate sum, 1s avg, Detector1+2",int(smaxz)+1, sminz,smaxz+1, 100,0 ,maxdose*3);
  drratio1_1s_vs_z = new TH2D("drratio1_1s_vs_z","Ouside/Internal Dose Rate ratio, 1s avg",int(smaxz)+1, sminz,smaxz+1, 100,0 ,2E-5);
  drratio2_1s_vs_z = new TH2D("drratio2_1s_vs_z","Outside/Internal Dose Rate ratio, 1s avg",int(smaxz)+1, sminz,smaxz+1, 100,0 ,2E-5);  
  
  drin1_1m_vs_z = new TH2D("drin1_1m_vs_z","Internal Dose Rate, 1m avg, 2m distance",int(smaxz)+1, sminz,smaxz+1, 100,0 ,maxdose*2E5);
  drin2_1m_vs_z = new TH2D("drin2_1m_vs_z","Internal Dose Rate, 1m avg, 2m distance",int(smaxz)+1, sminz,smaxz+1, 100,0 ,maxdose*2E5);
  drout1_1m_vs_z = new TH2D("drout1_1m_vs_z","Outside Dose Rate, 1m avg",int(smaxz)+1, sminz,smaxz+1, 100,0 ,maxdose*3);
  drout2_1m_vs_z = new TH2D("drout2_1m_vs_z","Outside Dose Rate, 1m avg",int(smaxz)+1, sminz,smaxz+1, 100,0 ,maxdose*3);

  drsum_1m_vs_z = new TH2D("drsum_1m_vs_z","Dose Rate sum, 1m avg, Detector1+2",int(smaxz)+1, sminz,smaxz+1, 100,0 ,maxdose*3);
  drratio1_1m_vs_z = new TH2D("drratio1_1m_vs_z","Outside/Internal Dose Rate ratio, 1m avg",int(smaxz)+1, sminz,smaxz+1, 100,0 ,2E-5);
  drratio2_1m_vs_z = new TH2D("drratio2_1m_vs_z","Outside/Internal Dose Rate ratio, 1m avg",int(smaxz)+1, sminz,smaxz+1, 100,0 ,2E-5);  
  
  if(nEntries1==nEntries2){
    for (int iEnt = 0; iEnt < nEntries1; iEnt++) {
      Long64_t tentry = myTree1->LoadTree(iEnt);
      b_z01->GetEntry(tentry);
      b_z02->GetEntry(tentry);
      b_din1->GetEntry(tentry);
      b_din2->GetEntry(tentry);
      b_drin1->GetEntry(tentry);
      b_drin2->GetEntry(tentry);
      b_drout1->GetEntry(tentry);
      b_drout2->GetEntry(tentry);
      b_drin1_1s->GetEntry(tentry);
      b_drin2_1s->GetEntry(tentry);
      b_drout1_1s->GetEntry(tentry);
      b_drout2_1s->GetEntry(tentry);
      b_drin1_1m->GetEntry(tentry);
      b_drin2_1m->GetEntry(tentry);
      b_drout1_1m->GetEntry(tentry);
      b_drout2_1m->GetEntry(tentry);
      
      for(int jEnt=0; jEnt<t_z01->size();jEnt++){
	din1_vs_z->Fill(t_z01->at(jEnt),t_din1->at(jEnt));
	din2_vs_z->Fill(t_z02->at(jEnt),t_din2->at(jEnt));
	drin1_vs_z->Fill(t_z01->at(jEnt),t_drin1->at(jEnt));
	drin2_vs_z->Fill(t_z02->at(jEnt),t_drin2->at(jEnt));
	drout1_vs_z->Fill(t_z01->at(jEnt),t_drout1->at(jEnt));
	drout2_vs_z->Fill(t_z02->at(jEnt),t_drout2->at(jEnt));
	drsum_vs_z->Fill(t_z01->at(jEnt),t_drout1->at(jEnt)+t_drout2->at(jEnt));
	
	if(t_drin1->at(jEnt)>0.)drratio1_vs_z->Fill(t_z01->at(jEnt),t_drout1->at(jEnt)/t_drin1->at(jEnt));
	if(t_drin2->at(jEnt)>0.)drratio2_vs_z->Fill(t_z02->at(jEnt),t_drout2->at(jEnt)/t_drin2->at(jEnt));
	
	if(t_drin1_1s->at(jEnt)>-999.)drin1_1s_vs_z->Fill(t_z01->at(jEnt),t_drin1_1s->at(jEnt));
	if(t_drin2_1s->at(jEnt)>-999.)drin2_1s_vs_z->Fill(t_z02->at(jEnt),t_drin2_1s->at(jEnt));
	if(t_drout1_1s->at(jEnt)>-999.)drout1_1s_vs_z->Fill(t_z01->at(jEnt),t_drout1_1s->at(jEnt));
	if(t_drout1_1s->at(jEnt)>-999.)drout2_1s_vs_z->Fill(t_z02->at(jEnt),t_drout2_1s->at(jEnt));
	if(t_drin1_1s->at(jEnt)>0. && t_drout1_1s->at(jEnt)>-999.)drratio1_1s_vs_z->Fill(t_z01->at(jEnt),t_drout1_1s->at(jEnt)/t_drin1_1s->at(jEnt));
	if(t_drin2_1s->at(jEnt)>0. && t_drout2_1s->at(jEnt)>-999.)drratio2_1s_vs_z->Fill(t_z02->at(jEnt),t_drout2_1s->at(jEnt)/t_drin2_1s->at(jEnt));
	if(t_drout1_1s->at(jEnt)>-999. && t_drout2_1s->at(jEnt)>-999.)drsum_1s_vs_z->Fill(t_z01->at(jEnt),t_drout1_1s->at(jEnt)+t_drout2_1s->at(jEnt));
	
	if(t_drin1_1m->at(jEnt)>-999.)drin1_1m_vs_z->Fill(t_z01->at(jEnt),t_drin1_1m->at(jEnt));
	if(t_drin2_1m->at(jEnt)>-999.)drin2_1m_vs_z->Fill(t_z02->at(jEnt),t_drin2_1m->at(jEnt));
	if(t_drout1_1m->at(jEnt)>-999.)drout1_1m_vs_z->Fill(t_z01->at(jEnt),t_drout1_1m->at(jEnt));
	if(t_drout1_1m->at(jEnt)>-999.)drout2_1m_vs_z->Fill(t_z02->at(jEnt),t_drout2_1m->at(jEnt));
	if(t_drin1_1m->at(jEnt)>0. && t_drout1_1m->at(jEnt)>-999.)drratio1_1m_vs_z->Fill(t_z01->at(jEnt),t_drout1_1m->at(jEnt)/t_drin1_1m->at(jEnt));
	if(t_drin2_1m->at(jEnt)>0. && t_drout2_1m->at(jEnt)>-999.)drratio2_1m_vs_z->Fill(t_z02->at(jEnt),t_drout2_1m->at(jEnt)/t_drin2_1m->at(jEnt));
	if(t_drout1_1m->at(jEnt)>-999. && t_drout2_1m->at(jEnt)>-999.)drsum_1m_vs_z->Fill(t_z01->at(jEnt),t_drout1_1m->at(jEnt)+t_drout2_1m->at(jEnt));
	
	
      } 
    }
  }else{
    for (int iEnt = 0; iEnt < nEntries1; iEnt++) {
      Long64_t tentry = myTree1->LoadTree(iEnt);
      b_z01->GetEntry(tentry);
    }
    
    for (int iEnt = 0; iEnt < nEntries2; iEnt++) {
      Long64_t tentry = myTree2->LoadTree(iEnt);
      
      b_z02->GetEntry(tentry);
    }
    
  }
  
  gStyle->SetOptStat(0);
  TString psfilename="psfiles/"+string(m_output)+"_summary.ps";
  TLegend* leg = new TLegend(0.75, 0.75, 0.95, 0.95);
  din1_vs_z->SetLineColor(1);
  din1_vs_z->SetMarkerColor(1);
  din1_vs_z->GetXaxis()->SetTitle("z source (cm)");
  din1_vs_z->GetYaxis()->SetTitle("Dose (#muSv)");
  din1_vs_z->Draw();
  din2_vs_z->SetLineColor(2);
  din2_vs_z->SetMarkerColor(2);
  din2_vs_z->Draw("same");
  leg->AddEntry(din1_vs_z, "Detector 1 (z=0 cm)", "lp");
  leg->AddEntry(din2_vs_z, "Detector 2 (z=200 cm)", "lp");
  leg->Draw();

  c1->SaveAs("Cfiles/din.C");

  c1->SaveAs(psfilename+"(");
  
  c1 = new TCanvas();
  leg = new TLegend(0.75, 0.75, 0.95, 0.95);
  drin1_vs_z->SetLineColor(1);
  drin1_vs_z->SetMarkerColor(1);
  drin1_vs_z->GetXaxis()->SetTitle("z source (cm)");
  drin1_vs_z->GetYaxis()->SetTitle("Dose rate (#muSv/h)");
  drin1_vs_z->Draw();
  drin2_vs_z->SetMarkerColor(2);
  drin2_vs_z->SetLineColor(2);
  drin2_vs_z->Draw("same");
  leg->AddEntry(drin1_vs_z, "Detector 1 (z=0 cm)", "lp");
  leg->AddEntry(drin2_vs_z, "Detector 2 (z=200 cm)", "lp");
  leg->Draw();
  c1->SaveAs("Cfiles/drin.C");
  c1->SaveAs(psfilename);
  
  c1 = new TCanvas();
  leg = new TLegend(0.75, 0.75, 0.95, 0.95);
  drout1_vs_z->SetMarkerColor(1);
  drout1_vs_z->SetLineColor(1);
  drout1_vs_z->GetXaxis()->SetTitle("z source (cm)");
  drout1_vs_z->GetYaxis()->SetTitle("Dose rate (#muSv/h)");
  drout1_vs_z->Draw();
  drout2_vs_z->SetMarkerColor(2);
  drout2_vs_z->SetLineColor(2);
  drout2_vs_z->Draw("same");
  drsum_vs_z->SetMarkerColor(4);
  drsum_vs_z->SetLineColor(4);
  drsum_vs_z->Draw("same");
  leg->AddEntry(drout1_vs_z, "Detector 1 (z=0 cm)", "lp");
  leg->AddEntry(drout2_vs_z, "Detector 2 (z=200 cm)", "lp");
  leg->AddEntry(drsum_vs_z, "Detector 1+2", "lp");
  leg->Draw();
  c1->SaveAs("Cfiles/drout.C");
  c1->SaveAs(psfilename);

  c1 = new TCanvas();
  leg = new TLegend(0.75, 0.75, 0.95, 0.95);
  drratio1_vs_z->SetMarkerColor(1);
  drratio1_vs_z->SetLineColor(1);
  drratio1_vs_z->GetXaxis()->SetTitle("z source (cm)");
  drratio1_vs_z->GetYaxis()->SetTitle("Ratio");
  drratio1_vs_z->Draw();
  drratio2_vs_z->SetMarkerColor(2);
  drratio2_vs_z->SetLineColor(2);
  drratio2_vs_z->Draw("same");
  leg->AddEntry(drratio1_vs_z, "Detector 1 (z=0 cm)", "lp");
  leg->AddEntry(drratio2_vs_z, "Detector 2 (z=200 cm)", "lp");
  leg->Draw();
  c1->SaveAs("Cfiles/drratio.C");
  c1->SaveAs(psfilename);

    //1s
  c1 = new TCanvas();
  leg = new TLegend(0.75, 0.75, 0.95, 0.95);
  drin1_1s_vs_z->SetMarkerColor(1);
  drin1_1s_vs_z->SetLineColor(1);
  drin1_1s_vs_z->GetXaxis()->SetTitle("z source (cm)");
  drin1_1s_vs_z->GetYaxis()->SetTitle("Dose rate (#muSv/h)");
  drin1_1s_vs_z->Draw();
  drin2_1s_vs_z->SetMarkerColor(2);
  drin2_1s_vs_z->SetLineColor(2);
  drin2_1s_vs_z->Draw("same");
  leg->AddEntry(drin1_1s_vs_z, "Detector 1 (z=0 cm)", "lp");
  leg->AddEntry(drin2_1s_vs_z, "Detector 2 (z=200 cm)", "lp");
  leg->Draw();
  c1->SaveAs("Cfiles/drin_1s.C");
  c1->SaveAs(psfilename);

  c1 = new TCanvas();
  leg = new TLegend(0.75, 0.75, 0.95, 0.95);
  drout1_1s_vs_z->SetMarkerColor(1);
  drout1_1s_vs_z->SetLineColor(1);
  drout1_1s_vs_z->GetXaxis()->SetTitle("z source (cm)");
  drout1_1s_vs_z->GetYaxis()->SetTitle("Dose rate (#muSv/h)");
  drout1_1s_vs_z->Draw();
  drout2_1s_vs_z->SetMarkerColor(2);
  drout2_1s_vs_z->SetLineColor(2);
  drout2_1s_vs_z->Draw("same");
  drsum_1s_vs_z->SetMarkerColor(4);
  drsum_1s_vs_z->SetLineColor(4);
  drsum_1s_vs_z->Draw("same");
  leg->AddEntry(drout1_1s_vs_z, "Detector 1 (z=0 cm)", "lp");
  leg->AddEntry(drout2_1s_vs_z, "Detector 2 (z=200 cm)", "lp");
  leg->AddEntry(drsum_1s_vs_z, "Detector 1+2", "lp");
  leg->Draw();
  c1->SaveAs("Cfiles/drout_1s.C");
  c1->SaveAs(psfilename);
  
  c1 = new TCanvas();
  leg = new TLegend(0.75, 0.75, 0.95, 0.95);
  drratio1_1s_vs_z->SetMarkerColor(1);
  drratio1_1s_vs_z->SetLineColor(1);
  drratio1_1s_vs_z->GetXaxis()->SetTitle("z source (cm)");
  drratio1_1s_vs_z->GetYaxis()->SetTitle("Ratio");
  drratio1_1s_vs_z->Draw();
  drratio2_1s_vs_z->SetMarkerColor(2);
  drratio2_1s_vs_z->SetLineColor(2);
  drratio2_1s_vs_z->Draw("same");
  leg->AddEntry(drratio1_1s_vs_z, "Detector 1 (z=0 cm)", "lp");
  leg->AddEntry(drratio2_1s_vs_z, "Detector 2 (z=200 cm)", "lp");
  leg->Draw();
  c1->SaveAs("Cfiles/drratio_1s.C");
  c1->SaveAs(psfilename);

  //1m
  c1 = new TCanvas();
  leg = new TLegend(0.75, 0.75, 0.95, 0.95);
  drin1_1m_vs_z->SetMarkerColor(1);
  drin1_1m_vs_z->SetLineColor(1);
  drin1_1m_vs_z->GetXaxis()->SetTitle("z source (cm)");
  drin1_1m_vs_z->GetYaxis()->SetTitle("Dose rate (#muSv/h)");
  drin1_1m_vs_z->Draw();
  drin2_1m_vs_z->SetMarkerColor(2);
  drin2_1m_vs_z->SetLineColor(2);
  drin2_1m_vs_z->Draw("same");
  leg->AddEntry(drin1_1m_vs_z, "Detector 1 (z=0 cm)", "lp");
  leg->AddEntry(drin2_1m_vs_z, "Detector 2 (z=200 cm)", "lp");
  leg->Draw();
  c1->SaveAs("Cfiles/drin_1m.C");
  c1->SaveAs(psfilename);
  
  c1 = new TCanvas();
  leg = new TLegend(0.75, 0.75, 0.95, 0.95);
  drout1_1m_vs_z->SetMarkerColor(1);
  drout1_1m_vs_z->SetLineColor(1);
  drout1_1m_vs_z->GetXaxis()->SetTitle("z source (cm)");
  drout1_1m_vs_z->GetYaxis()->SetTitle("Dose rate (#muSv/h)");
  drout1_1m_vs_z->Draw();
  drout2_1m_vs_z->SetMarkerColor(2);
  drout2_1m_vs_z->SetLineColor(2);
  drout2_1m_vs_z->Draw("same");
  drsum_1m_vs_z->SetMarkerColor(4);
  drsum_1m_vs_z->SetLineColor(4);
  drsum_1m_vs_z->Draw("same");
  leg->AddEntry(drout1_1m_vs_z, "Detector 1 (z=0 cm)", "lp");
  leg->AddEntry(drout2_1m_vs_z, "Detector 2 (z=200 cm)", "lp");
  leg->AddEntry(drsum_1m_vs_z, "Detector 1+2", "lp");
  leg->Draw();
  c1->SaveAs("Cfiles/drout_1m.C");
  c1->SaveAs(psfilename);
  
  c1 = new TCanvas();
  leg = new TLegend(0.75, 0.75, 0.95, 0.95);
  drratio1_1m_vs_z->SetMarkerColor(1);
  drratio1_1m_vs_z->SetLineColor(1);
  drratio1_1m_vs_z->GetXaxis()->SetTitle("z source (cm)");
  drratio1_1m_vs_z->GetYaxis()->SetTitle("Ratio");
  drratio1_1m_vs_z->Draw();
  drratio2_1m_vs_z->SetMarkerColor(2);
  drratio2_1m_vs_z->SetLineColor(2);
  drratio2_1m_vs_z->Draw("same");
  leg->AddEntry(drratio1_1m_vs_z, "Detector 1 (z=0 cm)", "lp");
  leg->AddEntry(drratio2_1m_vs_z, "Detector 2 (z=200 cm)", "lp");
  leg->Draw();
  c1->SaveAs("Cfiles/drratio_1m.C");
  c1->SaveAs(psfilename+")");
  
  }

  myFile.Close(); // Close file

}
