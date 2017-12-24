#ifndef COMMON_HELPERS_STRINGHELPER_H_
#define COMMON_HELPERS_STRINGHELPER_H_

#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include "../types.h"

using namespace std;

class StringHelper
{
public:
	static StringVector split(const string &s, char delimiter);
	static StringVector split(const string &s, char delimiter, StringVector* out);

	static const string cleanup(const string &s);

private:
	StringHelper(); // Disable direct object creation from class
};

#endif /* COMMON_HELPERS_STRINGHELPER_H_ */
