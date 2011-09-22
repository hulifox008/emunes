#include <stdlib.h>
#include "bus.h"

struct nesbus *bus_new()
{
    return (struct nesbus*)malloc(sizeof(struct nesbus));
}
