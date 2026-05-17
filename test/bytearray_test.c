#include <stdio.h>
#include <d_capi.h>

typedef struct byte_array BTAY;

int main(int argc,char** argv){

    c_say_hello();
    int64_t pos_s[64]={0};
    BTAY* hexs= hexstrTohex_ary("1a cf fc 1d 1a cf fc 1d "
                                "1a cf fc 1d 1a cf fc 1d "
                                "1a cf fc 1d 1a cf fc 1d ");
    int count=0;
    int64_t pos=-1;
    while(true){
        pos=hexs->ops->indexof_hex(hexs,pos+1,"1a cf fc 1d");
        if(pos<0){
            break;
        }
        pos_s[count]=pos;
        count++;
    }
    for(int i=0;i<count;i++){
        printf("pos[%d]:%ld\n",i,pos_s[i]);
    }
    
    return 0;
}