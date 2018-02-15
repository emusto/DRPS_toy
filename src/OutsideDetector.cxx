/***************************************************************************
 * @Project: DRPS_TOY - ROOT-based analysis framework for SwissFEL DRPS    *
 *                                                                         *
 * @author Elisa Musto <Elisa.Musto@psi.ch> - Paul Scherrer Institute      *
 *                                                                         *
 * 03/10/2015                                                              *
 ***************************************************************************/

#include "OutsideDetector.h"

OutsideDetector::OutsideDetector(float sensitivity, float integrationtime, float y, float z, float nuisance, std::string id):
  BaseDetector(sensitivity,integrationtime,y,z,nuisance,id),
  m_ox(365.),
  m_concretewidth(150.),
  m_attenuation(15.),
  idet(sensitivity,integrationtime,y,z,nuisance,"R"+id)
  
  
{
  m_logger.SetSource("OutsideDetector");
  Setx(m_ox);
}

OutsideDetector::~OutsideDetector()
{
  
}

float OutsideDetector::sdistance(float z0)
{
  
  return sqrt( m_x*m_x + m_y*m_y + (m_z-z0)*(m_z-z0) );
  
}

float OutsideDetector::oangle(float z0)
{
  return atan((m_z-z0)/m_x);
  
}

double OutsideDetector::idose( double d0, float z0)
{

  return  idet.dose(d0,z0);

}

double OutsideDetector::dose( double d0, float z0)
{

  double  idose=idet.dose(d0,z0);
  double  idistance=idet.sdistance(z0);
  double  det_distance=sdistance(z0);
  double  det_angle=oangle(z0);
  double  effwidth = m_concretewidth/cos(det_angle);
  return idose * idistance * idistance *exp(-(effwidth/m_attenuation))/ (det_distance*det_distance);
}

double OutsideDetector::idmeasureddose( double ncounts, double ncountserr)
{

  return idet.measureddose(ncounts, ncountserr);
}

double OutsideDetector::measureddose( double ncounts, double ncountserr, float z0)
{
  double  idmdose=idmeasureddose(ncounts, ncountserr);
  double  idistance=idet.sdistance(z0);
  double  det_distance=sdistance(z0);
  double  det_angle=oangle(z0);
  double  effwidth = m_concretewidth/cos(det_angle);
  return idmdose * idistance * idistance *exp(-(effwidth/m_attenuation))/ (det_distance*det_distance);
}

double OutsideDetector::measureddose( double idmdose, float z0)
{
  double  idistance=idet.sdistance(z0);
  double  det_distance=sdistance(z0);
  double  det_angle=oangle(z0);
  double  effwidth = m_concretewidth/cos(det_angle);
  return idmdose * idistance * idistance *exp(-(effwidth/m_attenuation))/ (det_distance*det_distance);
}


