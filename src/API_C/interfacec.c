#include "interfacec.h"

void c_say_hello()
{
#ifdef _FILE_OFFSET_BITS
	printf("_FILE_OFFSET_BITS is %d\n", _FILE_OFFSET_BITS);
#endif
	printf("this is hello from c\n");
}



int64_t
dg_append(
	char **rt, char *src1, int64_t c1_len, char *src2, int64_t c2_len, bool free)
{
	int64_t sum = c1_len + c2_len;
	if (src1 != NULL && src2 != NULL)
	{
		(*rt) = (char *)malloc(sizeof(char) * sum);
		if (rt == NULL)
		{
			printf("dg_append>> malloc fail");
			return 0;
		}

		for (int i = 0; i < c1_len; i++)
		{
			(*rt)[i] = src1[i];
		}
		for (int i = 0; i < c2_len; i++)
		{
			int offset = i + c1_len;
			(*rt)[offset] = src2[i];
		}
	}
	else
	{
		return 0;
	}

	return sum;
}
void dg_append_free(char *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
	}
}

