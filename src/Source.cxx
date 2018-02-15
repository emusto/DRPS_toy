/***************************************************************************
 * @Project: DRPS_TOY - ROOT-based analysis framework for SwissFEL DRPS    *
 *                                                                         *
 * @author Elisa Musto <Elisa.Musto@psi.ch> - Paul Scherrer Institute      *
 *                                                                         *
 * 05/10/2015                                                              *
 ***************************************************************************/

#include "Source.h"
#include <iostream>
#include <time.h>
Source::Source(float dose, float doseuncert, float frequency, bool randz, float minz, float maxz):
  m_dose(dose),
  m_doseuncert(doseuncert),
  m_frequency(frequency),
  m_isrand(randz),
  m_zmin(minz),
  m_zmax(maxz),
  m_logger("Source"),
  m_random(0)
{
  if(m_isrand){

    time_t timer;
    struct tm y2k = {0};
    double seconds;
    y2k.tm_hour = 0;   y2k.tm_min = 0; y2k.tm_sec = 0;
    y2k.tm_year = 100; y2k.tm_mon = 0; y2k.tm_mday = 1;

    time(&timer);  /* get current time; same as: timer = time(NULL)  */
    seconds = difftime(timer,mktime(&y2k));
    m_random.SetSeed(seconds);
    m_z=m_random.Uniform(m_zmin, m_zmax);
  }else{
    if(fabs(minz-maxz)>1E-7){
      m_logger<<WARNING<<"Fixed z for source emission has been chosen, but min z != max z: will set z = min z "<<Logger::endmsg;
    }
    m_z=m_zmin=m_zmax=minz;
  }
}

Source::Source():
  m_dose(5.),
  m_doseuncert(0.1),
  m_frequency(100),
  m_isrand(true),
  m_zmin(0.),
  m_zmax(300.),
  m_logger("Source"),
  m_random(0)
  
{
  m_logger<<DEBUG<<" Using Default settings:"<<Logger::endmsg;
  m_logger<<DEBUG<<" * Uniform random z in range: [0 - 300] cm"<<Logger::endmsg;
  m_logger<<DEBUG<<" * Dose: 5 mSv pm 10%"<<Logger::endmsg;
  m_z=m_random.Uniform(m_zmin, m_zmax);
 
}

Source::~Source(){
}

float Source::GetSmearedDose(){
  m_logger<<DEBUG<<"Dose uncertainty set to "<<m_doseuncert<<Logger::endmsg;
  if(m_doseuncert>0.){
    return m_dose*(1+m_random.Gaus(0.,m_doseuncert));
  }else{
    m_logger<<WARNING<<"Dose uncertainty set to 0, will return unsmeared dose."<<Logger::endmsg;
    return m_dose;
  }

}
