#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define SetDbgMemHooks() \
  _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF | \
    _CRTDBG_ALLOC_MEM_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))
#else
#define SetDbgMemHooks() ((VOID)0)
#endif
#include <stdlib.h>

#define MAX 50

typedef struct tagLIST LIST;
struct tagLIST
{
  char Str[MAX];
  LIST *Next, *Prev;
};

void DisplayList( LIST *L );
int AddToListFront( LIST **L, char *NewStr );
int AddToListBack( LIST **L, char *NewStr );
int DelFromListFront( LIST **L );
int DelFromListBack( LIST **L );
void ClearList( LIST **L );
int ShiftPrev( LIST **L );
int ShiftNext( LIST **L );
