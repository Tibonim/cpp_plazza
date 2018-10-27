#include "Format.hh"

namespace utils {

  Format::Format(std::string const &fileName)
  {
    std::ifstream t(fileName.c_str());
    if (!t)
      throw plazza::FormatException("Cannot open file \"" + fileName + "\"",
			    "Format::Format()");
    std::string str((std::istreambuf_iterator<char>(t)),
		    std::istreambuf_iterator<char>());
    ParseInput parser;
    std::string command;
    std::string regex;
    parser.setString(str);
    t.close();
    do
      {
	parser.parse('=');
	command = parser.getString();
	parser.parse('\n');
	regex = parser.getString();
	if (command.size() && regex.size() == 0)
	  throw plazza::FormatException("Missing paramter", "Format()");
	else if (command.size() && regex.size())
	  _dictionary[command] = regex;
      } while (regex.size());
    _dictionary[""] = std::string("");
  }

  std::string const &Format::find(std::string const &command) const {
    auto it = _dictionary.find(command);
    if (it == _dictionary.end())
      return (_dictionary.find("")->second);
    return (it->second);
  }
}
