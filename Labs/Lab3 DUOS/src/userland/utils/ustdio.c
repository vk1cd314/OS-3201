#include <ustdio.h>

void uprintf(char *format,...)
{
    char *tr;
	uint32_t i;
	uint8_t *str;
	va_list list;
	double dval;

    char ans[256];
    int ptr = 0;
	//uint32_t *intval;
	va_start(list,format);
	for(tr = format;*tr != '\0';tr++)
	{
		while(*tr != '%' && *tr!='\0')
		{
            ans[ptr] = *tr;
            ptr++;
		    tr++;
		}
		if(*tr == '\0') break;
		tr++;
		switch (*tr)
		{
            case 'c':
                //Cast character into int
                i = va_arg(list,int);
                //Assign it to our built string
                ans[ptr] = i;
                ptr++;
                break;
            case 'd': i = va_arg(list,int);
                if(i<0)
                {
                    //negative value
                    ans[ptr] = '-';
                    ptr++;
                    i=-i;				
                }
                //Convert to base 10
                //cast it into character array
                uint8_t* cur =  convert(i,10);
                int temp_ptr = 0;
                while(cur[temp_ptr])
                {
                    ans[ptr] = cur[temp_ptr];
                    ptr++;
                    temp_ptr++;
                }
                break;
            case 'o': 
                i = va_arg(list,int);
                //Same code copy-paste
                if(i<0)
                {
                    //negative value
                    ans[ptr] = '-';
                    ptr++;
                    i=-i;				
                }
                //Convert to base 8
                //cast it into character array
                cur =  convert(i,8);
                temp_ptr = 0;
                while(cur[temp_ptr])
                {
                    ans[ptr] = cur[temp_ptr];
                    ptr++;
                    temp_ptr++;
                }
                break;
            case 'x': 
                i = va_arg(list,int);
                if(i<0)
                {
                    //negative value
                    ans[ptr] = '-';
                    ptr++;
                    i=-i;				
                }
                //Convert to base 16
                //cast it into character array
                cur =  convert(i,16);
                temp_ptr = 0;
                while(cur[temp_ptr])
                {
                    ans[ptr] = cur[temp_ptr];
                    ptr++;
                    temp_ptr++;
                }
                break;
            case 's': 
                //Direct assigning for string
                str = va_arg(list,uint8_t*);
                cur = str;
                temp_ptr = 0;
                while(cur[temp_ptr])
                {
                    ans[ptr] = cur[temp_ptr];
                    ptr++;
                    temp_ptr++;
                }
                break;
            case 'f': 
                dval = va_arg(list,double);
                cur = (uint8_t*)float2str(dval);
                temp_ptr = 0;
                while(cur[temp_ptr] != 0)
                {
                    ans[ptr] = cur[temp_ptr];
                    ptr++;
                    temp_ptr++;
                }
                break;	
            default:
                break;
		}
	}
    ans[ptr]=0;
    

	va_end(list);
    char *return_param = ans;
    write_user(1,return_param);
}
