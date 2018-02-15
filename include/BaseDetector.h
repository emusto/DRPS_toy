/***************************************************************************
 * @Project: DRPS_TOY - ROOT-based analysis framework for SwissFEL DRPS    *
 *                                                                         *
 * @author Elisa Musto <Elisa.Musto@psi.ch> - Paul Scherrer Institute      *
 *                                                                         *
 * 05/10/2015                                                              *
 ***************************************************************************/

#ifndef BASEDETECTOR_H
#define BASEDETECTOR_H
#include <string>
#include <vector>

#include "TRandom3.h"
#include "Logger.h"


class BaseDetector
{

 protected:
  float m_sensitivity;
  float m_integrationtime;
  float m_x;
  float m_y;
  float m_z;
  float m_nuisance;
  std::string m_id;
  mutable Logger m_logger;
  TRandom3  m_random;
 public:
  BaseDetector(float sensitivity, float integrationtime, float x, float y, float z, float nuisance, std::string id);
  BaseDetector(float sensitivity, float integrationtime, float y, float z, float nuisance, std::string id);
  virtual ~BaseDetector();

  //Getters
  float GetSensitivity() { return m_sensitivity; };
  float GetNuisance() { return m_nuisance; };
  float GetIntegrationtime(){return m_integrationtime;};
  float Getx() { return m_x; };
  float Gety() { return m_y; };
  float Getz() { return m_z; };
  std::string GetId() { return m_id; };

  //Setters
  void SetSensitivity(float sensitivity) { m_sensitivity = sensitivity; };
  void SetIntegrationtime(float integrationtime) { m_integrationtime = integrationtime; };
  void SetNuisance(float nuisance) { m_nuisance = nuisance; };
  void Setx(float x) { m_x = x; };
  void Sety(float y) { m_y = y; };
  void Setz(float z) { m_z = z; };
  void SetId(std::string id) { m_id = id;};
  void SetCoordinates(float x, float y, float z);

  //Common to all detectors  
  virtual float sdistance(float z0=0.) = 0;
  virtual double dose(double d0=0.,float z0=0.) = 0;
  double ncounts(double dose);
  double nPoissoncounts(double dose);
  double ncounts_rel_err(double ncounts);
 
};

#endif 
