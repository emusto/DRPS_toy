/***************************************************************************
 * @Project: DRPS_TOY - ROOT-based analysis framework for SwissFEL DRPS    *
 *                                                                         *
 * @author Elisa Musto <Elisa.Musto@psi.ch> - Paul Scherrer Institute      *
 *                                                                         *
 * 05/10/2015                                                              *
 ***************************************************************************/

#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <sstream>
#include "MessageType.h"
#include "LoggerWriter.h"

using namespace std;

class LoggerWriter;

class Logger:public ostringstream {
  
  
 public:
  
  Logger( const string& source );
  Logger( const Logger& parent );
  virtual ~Logger();
    
  Logger& operator= ( const Logger& parent );
 
  static Logger& endmsg( Logger& logger );
 
  Logger& operator<< ( Logger& ( *_f )( Logger& ) );
  Logger& operator<< ( ostream& ( *_f )( ostream& ) );
  Logger& operator<< ( ios& ( *_f )( ios& ) );
  
  Logger& operator<< ( MessageType type );
 
  
  template < class T > Logger& operator<< ( T arg ) {
    if( m_activeType >= m_logWriter->GetMinType() ) {
      ( * ( ostringstream* ) this ) << arg;
    }
    return *this;
  }
  
  void Send( MessageType type, const string& ) const;
  const char* GetSource() const;
  void SetSource(const string& );
 private:
  void Send();
  
  string    m_strSource;
  LoggerWriter*    m_logWriter;
  MessageType       m_activeType;
 
 }; // class Logger
 
 //                                                                  //
 //   To speed up the code a bit, the following operators are        //
 //   declared 'inline'.                                             //
 //                                                                  //
 
 inline Logger& Logger::operator<< ( Logger& ( *_f )( Logger& ) ) {
 
    return ( _f )( *this );
 
 }
 
 inline Logger& Logger::operator<< ( ostream& ( *_f )( ostream& ) ) {
 
    if( m_activeType >= m_logWriter->GetMinType() ) {
       ( _f )( *this );
    }
    return *this;
 
 }
 
 inline Logger& Logger::operator<< ( ios& ( *_f )( ios& ) ) {
 
    if( m_activeType >= m_logWriter->GetMinType() ) {
       ( _f )( *this );
    }
    return *this;
 
 }
 
 inline Logger& Logger::operator<< ( MessageType type ) {
 
    m_activeType = type;
    return *this;
 
 }


#endif
