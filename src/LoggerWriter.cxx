/***************************************************************************
 * @Project: DRPS_TOY - ROOT-based analysis framework for SwissFEL DRPS    *
 *                                                                         *
 * @author Elisa Musto <Elisa.Musto@psi.ch> - Paul Scherrer Institute      *
 *                                                                         *
 * 05/10/2015                                                              *
 ***************************************************************************/


#include <iostream>
#include "LoggerWriter.h"
using namespace std;

#define USE_COLORED_CONSOLE

using namespace std;
 
LoggerWriter* LoggerWriter::m_instance = 0;

LoggerWriter* LoggerWriter::Instance() {
  
  if( ! m_instance ) {
    m_instance = new LoggerWriter();
  }
  
  return m_instance;
}
 
LoggerWriter::~LoggerWriter() {
  
}
 
void LoggerWriter::Write( MessageType type, const string& line ) const {
  
  if( type < m_mintype ) return;
  map< MessageType, string >::const_iterator stype;

  if( ( stype = m_typeMap.find( type ) ) == m_typeMap.end() ) return;

#ifdef USE_COLORED_CONSOLE

  cout << m_colorMap.find( type )->second << " (" << stype->second << ")  "
       << line << "\033[0m" << endl;
#else
  cout << " (" << stype->second << ")  " << line  << endl;
  
#endif // USE_COLORED_CONSOLE
  
  return;
  
}


MessageType LoggerWriter::GetMinType() const{

  return m_mintype;

}
void LoggerWriter::SetMinType(MessageType mtype){

  m_mintype=mtype;

}

LoggerWriter::LoggerWriter() {
 
  m_typeMap[ DEBUG ]   = " DEBUG ";
  m_typeMap[ INFO ]    = " INFO  ";
  m_typeMap[ WARNING ] = "WARNING";
  m_typeMap[ ERROR ]   = " ERROR ";
  m_typeMap[ FATAL ]   = " FATAL ";
  
  m_colorMap[ DEBUG ]   = "\033[34m";
  m_colorMap[ INFO ]    = "\033[32m";
  m_colorMap[ WARNING ] = "\033[35m";
  m_colorMap[ ERROR ]   = "\033[31m";
  m_colorMap[ FATAL ]   = "\033[1;31;40m";
  
  m_mintype = INFO;
  
 }
