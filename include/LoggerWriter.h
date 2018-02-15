/***************************************************************************
 * @Project: DRPS_TOY - ROOT-based analysis framework for SwissFEL DRPS    *
 *                                                                         *
 * @author Elisa Musto <Elisa.Musto@psi.ch> - Paul Scherrer Institute      *
 *                                                                         *
 * 05/10/2015                                                              *
 ***************************************************************************/

#ifndef LOGGERWRITER_H
#define LOGGERWRITER_H

#include <string>
#include <map>
#include "MessageType.h"

using namespace std;

class LoggerWriter{

 public:
  static LoggerWriter* Instance();
  ~LoggerWriter();
 
  void Write( MessageType type, const string& line ) const;
 
  void SetMinType( MessageType type );
  MessageType GetMinType() const;
 
 protected:
    LoggerWriter();
    
 private:
    static LoggerWriter* m_instance;
 
    map< MessageType, string > m_typeMap;
    map< MessageType, string > m_colorMap;
    MessageType  m_mintype;
 

  };


#endif
