/***************************************************************************
 * @Project: DRPS_TOY - ROOT-based analysis framework for SwissFEL DRPS    *
 *                                                                         *
 * @author Elisa Musto <Elisa.Musto@psi.ch> - Paul Scherrer Institute      *
 *                                                                         *
 * 03/10/2015                                                              *
 ***************************************************************************/

#ifndef ROOFDETECTOR_H
#define ROOFDETECTOR_H

#include "BaseDetector.h"

class RoofDetector : virtual public BaseDetector
{

 protected:
  float m_backscattering;
  using BaseDetector::Setx;
  using BaseDetector::SetCoordinates;
  //using BaseDetector::m_logger;
  
 public:
  ~RoofDetector();
  RoofDetector(float sensitivity, float integrationtime, float y, float z, float nuisance,std::string id);
  virtual float sdistance(float z0);
  virtual double dose(double d0, float z0);
  double measureddose(double ncounts, double ncountserr);

};


#endif 
