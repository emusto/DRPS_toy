/***************************************************************************
 * @Project: DRPS_TOY - ROOT-based analysis framework for SwissFEL DRPS    *
 *                                                                         *
 * @author Elisa Musto <Elisa.Musto@psi.ch> - Paul Scherrer Institute      *
 *                                                                         *
 * 05/10/2015                                                              *
 ***************************************************************************/
//ME: Note - the logging classes are based on SFrame code


#include "Logger.h"
#include <iomanip>

using namespace std;
static const string::size_type MAXIMUM_SOURCE_NAME_LENGTH = 18;

 
 
Logger::Logger( const string& source )
  :  m_strSource( source ), m_activeType( INFO ) {
  
  m_logWriter = LoggerWriter::Instance();
  
 }
 
Logger::Logger( const Logger& parent )
    : basic_ios< Logger::char_type, Logger::traits_type >(),
  ostringstream() {
  
  *this = parent;
  
}
 
Logger::~Logger() {
 
}

void Logger::SetSource( const string& source ) {

  m_strSource = source;
  return;
}

/**
 * @returns The string that should be printed as the source of the log messages
 */
const char* Logger::GetSource() const {

  return m_strSource.c_str();

}
 
Logger& Logger::operator= ( const Logger& parent ) {
 
  m_strSource = parent.m_strSource;
  m_logWriter = LoggerWriter::Instance();
  
  return *this;
  
}
 
void Logger::Send( const MessageType type, const string& message ) const {
  
  if( type < m_logWriter->GetMinType() ) return;
 
  string::size_type previous_pos = 0, current_pos = 0;
  
  //
  // Make sure the source name is no longer than MAXIMUM_SOURCE_NAME_LENGTH:
  //
  string source_name;
  source_name = m_strSource;
  
  if( source_name.size() > MAXIMUM_SOURCE_NAME_LENGTH ) {
    source_name = source_name.substr( 0, MAXIMUM_SOURCE_NAME_LENGTH - 3 );
    source_name += "...";
  }
 
  //
  // Slice the recieved message into lines:
  //
  for( ; ; ) {
    
    current_pos = message.find( '\n', previous_pos );
    string line = message.substr( previous_pos, current_pos - previous_pos );
    
    ostringstream message_to_send;
    // I have to call the modifiers like this, otherwise g++ get's confused
    // with the operators...
    message_to_send.setf( ios::adjustfield, ios::left );
    message_to_send.width( MAXIMUM_SOURCE_NAME_LENGTH );
    message_to_send << source_name << " : " << line;
    m_logWriter->Write( type, message_to_send.str() );
    
    if( current_pos == message.npos ) break;
    previous_pos = current_pos + 1;
    
  }
  
  return;
  
}

void Logger::Send() {
  
  //
  // Call the "other" send(...) function:
  //
  this->Send( m_activeType, this->str() );
  
  //
  // Reset the stream buffer:
  //
  this->str( "" );
  
  return;
  
}

Logger& Logger::endmsg( Logger& logger ) {
  
  logger.Send();
  return logger;
  
}
