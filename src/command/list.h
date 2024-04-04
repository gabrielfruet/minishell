#ifndef __LIST__ 
#define __LIST__

#define IMPL_LIST_APPEND(name,type) \
void name(type ** list, type* toappend) { \
    if (list == NULL)  \
        return; \
    else if (*list == NULL) \
        *list = toappend; \
    else if ((*list)->next != NULL) \
        name(&((*list)->next), toappend);\
    else if ((*list)->next == NULL ) \
        (*list)->next = toappend; \
}
#endif
