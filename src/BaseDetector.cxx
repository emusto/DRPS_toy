/***************************************************************************
 * @Project: DRPS_TOY - ROOT-based analysis framework for SwissFEL DRPS    *
 *                                                                         *
 * @author Elisa Musto <Elisa.Musto@psi.ch> - Paul Scherrer Institute      *
 *                                                                         *
 * 05/10/2015                                                              *
 ***************************************************************************/

#include "BaseDetector.h"


BaseDetector::BaseDetector(float sensitivity, float integrationtime, float x, float y, float z, float nuisance, std::string id):
  m_sensitivity(sensitivity),
  m_integrationtime(integrationtime),
  m_x(x),
  m_y(y),
  m_z(z),
  m_nuisance(nuisance),
  m_id(id),
  m_logger("BaseDetector"),
  m_random(0)

{

}

BaseDetector::BaseDetector(float sensitivity, float integrationtime, float y, float z, float nuisance, std::string id):
  m_sensitivity(sensitivity),
  m_integrationtime(integrationtime),
  m_y(y),
  m_z(z),
  m_nuisance(nuisance),
  m_id(id),
  m_logger("BaseDetector"),
  m_random(0)

{

  m_x=185.;
}

BaseDetector::~BaseDetector(){

}

void BaseDetector::SetCoordinates(float x, float y, float z ){
  Setx(x);
  Sety(y);
  Setz(z); 
}

double BaseDetector::ncounts(double dose ){
  //  m_logger<<DEBUG<<"Computing ncounts, dose: "<<dose<<", counts before Poisson sampling: "<<(m_sensitivity*1000.*dose)<<Logger::endmsg;

  return m_sensitivity*1000.*dose;
}

double BaseDetector::nPoissoncounts(double dose ){
  //  m_logger<<DEBUG<<"Computing ncounts, dose: "<<dose<<", counts before Poisson sampling: "<<(m_sensitivity*1000.*dose)<<Logger::endmsg;

  return m_random.Poisson(m_sensitivity*1000.*dose);
}

double BaseDetector::ncounts_rel_err(double counts ){
  double rel_err=1.;
  if(counts>1.){
    rel_err=1./sqrt(counts);
  }
  return sqrt(m_nuisance*m_nuisance+rel_err*rel_err);   

}

