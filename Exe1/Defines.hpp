#define DEBUG 0 // 0=no debug couts, 1=debug couts
#define UNITTEST 0 // 0=no unit tests, 1=unit tests
#define NETWORK 0 // 0=no network capability, 1=network capability

#if DEBUG > 0
#define DEBUG_MSG(str) do { std::cout << str << std::endl; } while( false )
#else
#define DEBUG_MSG(str) do { } while ( false )
#endif
