#include <stdio.h>
#include <d_capi.h>

typedef struct byte_array BTAY;

int main(int argc,char** argv){

    c_say_hello();
    BTAY* hexs= hexstrTohex_ary("1a cf fc 1d 1a cf fc 1d "
                                "1a cf fc 1d 1a cf fc 1d "
                                "1a cf fc 1d 1a cf fc 1d ");

    int64_t pos= hexs->ops->indexof_hex(hexs,0,"1a cf fc 1d");
    printf("pos:%ld\n",pos);
    return 0;
}