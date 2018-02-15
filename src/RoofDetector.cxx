/***************************************************************************
 * @Project: DRPS_TOY - ROOT-based analysis framework for SwissFEL DRPS    *
 *                                                                         *
 * @author Elisa Musto <Elisa.Musto@psi.ch> - Paul Scherrer Institute      *
 *                                                                         *
 * 03/10/2015                                                              *
 ***************************************************************************/

#include "RoofDetector.h"

RoofDetector::RoofDetector(float sensitivity, float integrationtime, float y, float z, float nuisance, std::string id):
  BaseDetector(sensitivity, integrationtime, y,z,nuisance,id),
  m_backscattering(1.25)

{
  m_logger.SetSource("RoofDetector");
  
}

RoofDetector::~RoofDetector()
{
  
}

float RoofDetector::sdistance(float z0)
{

  return sqrt( m_x*m_x + m_y*m_y + (m_z-z0)*(m_z-z0) );


}

double RoofDetector::dose( double d0, float z0)
{
  const double x0 = 100.;
  float det_distance=sdistance(z0);
  return d0 * m_backscattering * x0 * x0 / (det_distance*det_distance);
}


double RoofDetector::measureddose( double ncounts, double ncountserr)
{
  double dose = ncounts/(1000.*m_sensitivity);
  return dose*(1+m_random.Gaus(0.,ncountserr));

}

