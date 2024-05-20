#ifndef _UTILS_H_
#define _UTILS_H_

#define SAFE_DELETE_PTR(ptr){ if(ptr){ delete ptr; ptr = NULL; } }
#define SAFE_DELETE_ARY(ptr){ if(ptr){ delete[] ptr; ptr = NULL; } }

#endif
