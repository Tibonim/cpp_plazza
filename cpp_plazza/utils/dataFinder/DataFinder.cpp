#include "DataFinder.hh"

namespace utils {

  DataFinder::DataFinder(Format &f) {
    _format = &f;
    _actions[KeyFinder::keyType::CESAR] = &DataFinder::_cesarFile;
    _actions[KeyFinder::keyType::XOR] = &DataFinder::_xorFile;
    _actions[KeyFinder::keyType::NOTFOUND] = &DataFinder::_notFound;
    _r = NULL;
  }

  std::string DataFinder::_preFind(std::string const &file, std::string const &format) const {
    if (_format->find(format).empty())
      throw plazza::DataFinderException{"format \"" + format + "\" not found", "DataFinder::find()"};
    std::ifstream t{file};
    if (!t)
      throw plazza::DataFinderException{"Cannot open \"" + file + "\"", "DataFinder::_preFind()"};
    std::string str{(std::istreambuf_iterator<char>(t)),
	std::istreambuf_iterator<char>()};
    return str;
  }

  std::vector<std::string> const &DataFinder::getOccurences() const {
    return _r->getOccurences();
  }

  void DataFinder::find(std::string const &file, std::string const &format) {
    std::string fileContent{_preFind(file, format)};
    std::string regex{_format->find(format)};

    if (_r)
      delete _r;
    _r = new Regex{regex};

    KeyFinder::keyType last = KeyFinder::keyType::NOTFOUND;
    KeyFinder kf;
    KeyFinder::key k;
    while (kf.find(fileContent)) {
      k = kf.getKey();
      if (static_cast<int>(last) + 1 == static_cast<int>(k.type)) {
	kf.reset();
      }
      auto it = _actions.find(k.type);
      if (it != _actions.end()) {
	(this->*(it->second))(fileContent, k);
      }
      kf.incrKey();
      last = k.type;
    }
  }

  bool DataFinder::_extractData(std::string const &content) const {
    return _r->find(content);
  }

  bool DataFinder::_xorFile(std::string const &file,
			    KeyFinder::key const &key) const {
    utils::Xor x;

    return _extractData(x.decrypt(file, key.xKey));
  }

  bool DataFinder::_cesarFile(std::string const &file,
			      KeyFinder::key const &key) const {
    utils::Cesar c;

    return _extractData(c.decrypt(file, key.cKey));
  }

  bool DataFinder::_notFound(std::string const &,
			     KeyFinder::key const &) const {
    return false;
  }

  bool DataFinder::_bruteClear(std::string const &file) const {
    return _extractData(file);
  }

  bool DataFinder::_bruteCesar(std::string const &file) const {
    Cesar c;
    uint8_t key;

    for (key = std::numeric_limits<uint8_t>::min();
	 key < std::numeric_limits<uint8_t>::max();
	 ++key)
      if (_extractData(c.decrypt(file, key)))
	return true;
    return _extractData(c.decrypt(file, key));
  }

  bool DataFinder::_bruteXor(std::string const &file) const {
    Xor c;

    std::string key{"1"};
    for (key[0] = std::numeric_limits<int8_t>::min();
	 key[0] < std::numeric_limits<int8_t>::max();
	 ++key[0]) {
      if (_extractData(c.decrypt(file, key)))
	return true;
    }
    if (_extractData(c.decrypt(file, key)))
	return true;
    key = "12";
    for (key[0] = std::numeric_limits<int8_t>::min();
	 key[0] < std::numeric_limits<int8_t>::max();
	 ++key[0]) {
      for (key[1] = std::numeric_limits<int8_t>::min();
	   key[1] < std::numeric_limits<int8_t>::max();
	   ++key[1])
	if (_extractData(c.decrypt(file, key)))
	  return true;
      if (_extractData(c.decrypt(file, key)))
	return true;
    }
    for (key[1] = std::numeric_limits<int8_t>::min();
	 key[1] < std::numeric_limits<int8_t>::max();
	 ++key[1])
      if (_extractData(c.decrypt(file, key)))
	return true;
    return _extractData(c.decrypt(file, key));
  }

  void DataFinder::_bruteForce(std::string const &file) const {
    if (_bruteClear(file))
      return ;
    if (_bruteCesar(file))
      return ;
    if (_bruteXor(file))
      return ;
  }
}
