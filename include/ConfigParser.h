/***************************************************************************
 * @Project: DRPS_TOY - ROOT-based analysis framework for SwissFEL DRPS    *
 *                                                                         *
 * @author Elisa Musto <Elisa.Musto@psi.ch> - Paul Scherrer Institute      *
 *                                                                         *
 * 09/10/2015                                                              *
 ***************************************************************************/


#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H
#include <string>
#include <map>
#include <fstream>
#include "Logger.h"

using namespace std;

class ConfigParser
{
 private:

  ifstream m_inputfile;
  string m_inputfilename;
  mutable Logger m_logger;

 public:
  ConfigParser(string);
  ~ConfigParser();
  map <string,string> ParseConfiguration();

};

#endif
