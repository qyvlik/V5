#ifndef V5_H
#define V5_H

#include <iostream>
#include <list>

#define V5_NAMESPACE_BEGIN  namespace V5 {

#define V5_NAMESPAE_END }


#define V5_HACK friend

#define V5_FRIEND friend

namespace V5 {

class Object;
class Arguments;
class Return;
class Variant;
class Runtime;
class Engine;

typedef std::pair<std::string, std::string> Token;
typedef std::list<Token> TokenList;


} //namespace V5


#endif // V5_H

