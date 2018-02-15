/***************************************************************************
 * @Project: DRPS_TOY - ROOT-based analysis framework for SwissFEL DRPS    *
 *                                                                         *
 * @author Elisa Musto <Elisa.Musto@psi.ch> - Paul Scherrer Institute      *
 *                                                                         *
 * 05/10/2015                                                              *
 ***************************************************************************/

#ifndef SOURCE_H
#define SOURCE_H
#include <string>
#include "TRandom3.h"
#include "Logger.h"

class Source

{

 protected:

  float m_dose;
  float m_doseuncert;
  int m_frequency;
  bool m_isrand;
  float m_zmin;
  float m_zmax;
  float m_z;
  Logger m_logger;
  TRandom3 m_random;
 public:
  ~Source();
  Source();
  Source(float dose, float doseuncert, float frequency, bool randomz, float minz, float mazx);
  void SetDose(float dose){m_dose=dose;};
  void SetFrequency(int frequency){m_frequency=frequency;};
  int GetFrequency(){ return m_frequency;};
  void SetDoseUncert(float doseuncert){m_doseuncert=doseuncert;};
  void Setzrange(float zmin, float zmax){m_zmin=zmin; m_zmax=zmax;};
  void Setz(float z){m_z=z;};
  float Getz(){return m_z;};
  float GetSmearedDose();  
};


#endif
