#ifndef _parser_
#define _parser_

#include <string>
#include <vector>
#include <map>

struct inPar{
  int type;
  std::string id;
  std::string val;
  std::vector<std::string> opts;
};

typedef std::map<std::string, inPar> MIPar;


class Parser{

public:

  enum {kNone=0, kDir, kAN, kUsr, kVbs, kSkim, kNMax, kSkip,
	kVar, kTree, kHisto, kWgtHisto, kDS, kFT, kSummary, kSyst,
	kCounter}; 

  static inPar parseLine(std::string line);
  static MIPar parseFile(std::string filename);

};

#endif
