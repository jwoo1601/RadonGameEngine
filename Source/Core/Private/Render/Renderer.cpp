For classes
should start with the prefix ‘X’ | start with capital letter
e.g. XObject | Object

For structs
should start with the prefix ’S’ | start with capital letter
e.g. SInitializer

For Global Functions
: the first letter of each word should be in caps | start with a capital, camelcase after
e.g. GetDirectXVersionInfo()

For Member Functions
: in camel case | camelcase
e.g. getName()

For Contant Variables
: the first letter of each word should be in capital | all lowercase, with underscore between words
e.g. static const TIndex NPos = (TIndex)-1;

For Macros / Macro Functions
: all the letters should be in capital | all capitals
#define RADON_VERSION 100
#define DEPRECATED(x) [[deprecated(x)]]

For Non Constant Member Variables
: camel Case with the prefix ‘m_’ before the name | m_ and camelcase
private:
int32 m_size;

For Global Variables
: should start with the prefix ‘G’ and the first letter of every following word should be in capital | first letter capital, camelcase after
SVersion GDirectXVersionInfo;

For Templated Classes or Aliases (using directives) / typedefs
: should start with the prefix ’T’ | prefix with capital T
template <typename Allocator>
class TVector {};
template <typename T>
using TEnableIf = …;
typedef T IntType;

For Template Parameters
: the first letter of each word should be in capital, and the name itself should be descriptive enough except for the case when the name of the parameters are for generic types (e.g. typename T) |
template <typename T, typename Allocator>

For boolean variables
: should start with the prefix ‘b’ | start with lowercase b (bFlag)
bool bSuccess;

