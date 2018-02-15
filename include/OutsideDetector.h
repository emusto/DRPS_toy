/***************************************************************************
 * @Project: DRPS_TOY - ROOT-based analysis framework for SwissFEL DRPS    *
 *                                                                         *
 * @author Elisa Musto <Elisa.Musto@psi.ch> - Paul Scherrer Institute      *
 *                                                                         *
 * 03/10/2015                                                              *
 ***************************************************************************/

#ifndef OUTSIDEDETECTOR_H
#define OUTSIDEDETECTOR_H

#include "RoofDetector.h"

class OutsideDetector :  public BaseDetector
{

 protected:
  float m_ox;
  float m_concretewidth;
  float m_attenuation;
  RoofDetector idet;
  using BaseDetector::Setx;
  using BaseDetector::SetCoordinates;
  
 public:
  ~OutsideDetector();
  OutsideDetector(float idsensitivity, float idintegrationtime, float y, float z,float nuisance, std::string id);
  virtual float sdistance(float z0);
  virtual double dose(double d0, float z0);
  double measureddose(double ncounts, double ncountserr, float z0);
  double measureddose(double idmdose, float z0);
  double idose(double d0, float z0);
  double idmeasureddose(double ncounts, double ncountserr);
  float oangle(float z0);
};

#endif 
