#include <stdlib.h>

#include "../snorlax.h"

extern object_t * object_func_rem(object_t * o) {
#ifndef   RELEASE
    snorlaxdbg(o == nil, false, "critical", "");
#endif // RELEASE

    free(o);

    return nil;
}