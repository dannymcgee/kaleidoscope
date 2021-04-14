#include <memory>
#include <string>
#include <vector>

template <typename T>
using Ptr = std::unique_ptr<T>;

template <typename T>
using Rc = std::shared_ptr<T>;

using std::string;
using std::vector;

#ifndef NULL
	#define NULL 0
#endif

#ifndef DEF_LOGGABLE
	#define DEF_LOGGABLE(type)\
		std::ostream& operator << (std::ostream&, ##type const&)
#endif

#ifndef IMPL_LOGGABLE
	#define IMPL_LOGGABLE(type, var_name)\
		std::ostream& operator << (std::ostream& stream, ##type const& ##var_name)
#endif
