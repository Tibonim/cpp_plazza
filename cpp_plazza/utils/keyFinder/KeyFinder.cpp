#include "KeyFinder.hh"

namespace utils {

  KeyFinder::KeyFinder() {
    this->_init();
  }
  void KeyFinder::_init() {
    this->reset();
     _start = true;
    _clear = false;
    _cesar = false;
    _key.type = KeyFinder::keyType::NONE;
  }

  void KeyFinder::reset() {
    _key.cKey = 0;
    _key.xKey = "1";
    _key.xKey[0] = std::numeric_limits<int8_t>::min();
  }

  bool KeyFinder::find(std::string const &fileContent) {
    if (!_clear && (_clearFile(fileContent)))
      return true;
    return false;
    if (!_cesar && (_cesarFile(fileContent))) {
      return true;
    }
    if ((_xorFile(fileContent)))
      {
	_start = false;
	return true;
      }
    _key.type = keyType::NOTFOUND;
    return false;
  }

  bool KeyFinder::_isFullPrintable(std::string const &content) {
    for (std::string::const_iterator it = content.cbegin();
	 it != content.cend(); ++it) {
      if ((!isprint(*it) && !isspace(*it) && *it != '\r') &&
	  static_cast<uint8_t>(*it) < 128)
	return false;
    }
    return true;
  }

  bool KeyFinder::_clearFile(std::string const &file) {
    _key.type = keyType::NONE;
    _clear = true;
    return _isFullPrintable(file);
  }

  bool KeyFinder::_cesarFile(std::string const &file) {
    Cesar c;

    _key.type = keyType::CESAR;
    for (; _key.cKey < std::numeric_limits<uint8_t>::max();
	 ++_key.cKey) {
      if (_isFullPrintable(c.decrypt(file, _key.cKey))) {
	return true;
      }
    }
    if (_isFullPrintable(c.decrypt(file, _key.cKey))) {
      _cesar = true;
      return true;
    }
    _cesar = true;
    return false;
  }

  bool KeyFinder::_xor2BytesFile(std::string const &file,
				 Xor &c) {
    for (; _key.xKey[0] < std::numeric_limits<int8_t>::max();
	 ++_key.xKey[0]) {
      for (_key.xKey[1] = ((_start) ? std::numeric_limits<int8_t>::min() : _key.xKey[1]);
	   _key.xKey[1] < std::numeric_limits<int8_t>::max();
	   ++_key.xKey[1]) {
	if (_isFullPrintable(c.decrypt(file, _key.xKey)))
	  return true;
	_start = true;
      }
      if (_isFullPrintable(c.decrypt(file, _key.xKey)))
	return true;
    }
    for (_key.xKey[1] = ((_start) ? std::numeric_limits<int8_t>::min() : _key.xKey[1]);
	   _key.xKey[1] < std::numeric_limits<int8_t>::max();
	   ++_key.xKey[1])
      if (_isFullPrintable(c.decrypt(file, _key.xKey)))
	return true;
    if (_isFullPrintable(c.decrypt(file, _key.xKey)))
	  return true;
    return false;
  }

  bool KeyFinder::_xorFile(std::string const &file) {
    Xor c;
    std::string result;
    _key.type = keyType::XOR;

    if (_key.xKey.size() == 1) {
      for (; _key.xKey[0] < std::numeric_limits<int8_t>::max();
	   ++_key.xKey[0])
	if (_isFullPrintable(c.decrypt(file, _key.xKey)))
	  return true;
      if (_isFullPrintable(c.decrypt(file, _key.xKey)))
	return true;
      _key.xKey = "12";
      _key.xKey[0] = std::numeric_limits<int8_t>::min();
      _key.xKey[1] = std::numeric_limits<int8_t>::min();
    }
    return _xor2BytesFile(file, c);
  }

  bool KeyFinder::incrKey() {
    if (_key.cKey != std::numeric_limits<uint8_t>::max())
      ++_key.cKey;
    if (_key.xKey.size() == 1) {
      if (_key.xKey[0] != std::numeric_limits<int8_t>::max())
	_key.xKey[0]++;
    }
    else if (_key.xKey.size() == 2) {
      if (_key.xKey[1] != std::numeric_limits<int8_t>::max())
	++_key.xKey[1];
      else if (_key.xKey[0] != std::numeric_limits<int8_t>::max()) {
	_key.xKey[0]++;
	_key.xKey[1] = std::numeric_limits<int8_t>::min();
      }
    }
    return true;
  }
}
