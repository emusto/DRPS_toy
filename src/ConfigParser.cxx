/***************************************************************************
 * @Project: DRPS_TOY - ROOT-based analysis framework for SwissFEL DRPS    *
 *                                                                         *
 * @author Elisa Musto <Elisa.Musto@psi.ch> - Paul Scherrer Institute      *
 *                                                                         *
 * 09/10/2015                                                              *
 ***************************************************************************/
#include "ConfigParser.h"


ConfigParser::ConfigParser(string inputfilename):
  m_inputfilename(inputfilename),
  m_logger("ConfigParser")
{
  m_inputfile.open(m_inputfilename);
  if(!m_inputfile.is_open()){
    m_logger<<ERROR<<"Could not open configuration file!"<<Logger::endmsg;
  }else{
    m_logger<<INFO<<"Openinig configuration file: "<<inputfilename<<Logger::endmsg;
  }
  //  ParseConfiguration(m_inputfile);
}


ConfigParser::~ConfigParser()
{
  m_inputfile.close();
}

map <string,string> ConfigParser::ParseConfiguration()

{
  map <string, string> options;

  for (string line; getline(m_inputfile, line); )
    {
      istringstream iss(line);
      string id, eq, val;
      if(!(iss>>id>>eq>>val)){
	if(id[0] == '#' ) continue;
	else m_logger<<ERROR<<"Error in configuration file line: "<<line<<Logger::endmsg;
      }
      else if(eq != "=" ){
	if(id[0] == '#' ) continue;
	else m_logger<<ERROR<<"Error in configuration file, key - value separator is "<<eq<<Logger::endmsg;}
      else options[id]=val;
      iss.clear();
    }
  return options;

}
