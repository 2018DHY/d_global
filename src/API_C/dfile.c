#include "dfile.h"

#include <stdlib.h>

int64_t
dg_read_all(char *path, char **rt)
{
	int unit = 4096;
	int count_unit = 1;
	int64_t size_rt = 0;
	int64_t cur_capacit = unit * count_unit;
	char *check = NULL;
	FILE *fl = fopen(path, "rb");

	if (fl != NULL)
	{
		printf("file open succese\n");
		(*rt) = (char *)malloc(sizeof(char) * cur_capacit);
		char ch;
		while (1)
		{
			ch = getc(fl);
			if (ch != EOF)
			{
				if (size_rt < cur_capacit)
				{
					(*rt)[size_rt] = ch;
				}
				else
				{
					count_unit++;
					cur_capacit = unit * count_unit;
					check = (char *)realloc((*rt), cur_capacit);
					if (check == NULL)
					{
						if ((*rt) != NULL)
						{
							free((*rt));
							return 0;
						}
						return 0;
					}
					(*rt) = check;
					(*rt)[size_rt] = ch;
				}
				size_rt++;
			}
			else
			{
				break;
			}
		}
		fclose(fl);
	}
	else
	{
		printf("dg_read_all>>open file failed");
		(*rt) = NULL;
		return 0;
	}

	return size_rt;
}

void dg_read_all_free(char *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
	}
}

int64_t
f_read_all(const char *const path, char **rt)
{
	FILE *fd = fopen(path, "rb");
	if (fd == NULL)
		return 0;
	fseek(fd, 0, SEEK_END);
	int64_t len = ftell(fd);
	fseek(fd, 0, SEEK_SET);
	*rt = (char *)malloc(sizeof(char) * len);
	if (*rt == NULL)
	{
		printf("f_read_all>>bad malloc");
		return 0;
	}
	if (fread(*rt, 1, len, fd) <= 0)
	{
		fclose(fd);
		*rt = NULL;
		return 0;
	}
	fclose(fd);
	return len;
}

void f_read_all_free(char *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
	}
}

int64_t fd_read_all(FILE *fd, char **rt, bool ex)
{
	if (fd == NULL)
		return 0;
	fseek(fd, 0, SEEK_END);
	int64_t len = ftell(fd);
	fseek(fd, 0, SEEK_SET);
	if (!ex)
	{
		*rt = (char *)malloc(sizeof(char) * len);
	}
	if (fread(*rt, sizeof(char), len, fd) <= 0)
	{
		return -1;
	}
	return len;
}
int64_t f_read_line(FILE *fd, char **rt, bool ex)
{
	// 目前只适用于win于linux,不适合mac
	if (fd == NULL)
	{
		return -1;
	}
	int64_t old_pos = ftell(fd);
	int64_t word_count = 0;
	char ch = 0;
	while (true)
	{
		ch = getc(fd);
		if (ch == EOF)
		{
			break;
		}
		word_count++;
		if (ch == '\n')
		{
			break;
		}
	}
	fseek(fd, old_pos, SEEK_SET);
	if (!ex)
	{
		*rt = (char *)malloc(word_count + 1);
		if (*rt == NULL)
		{
			return -1;
		}
	}
	if (fread(*rt, 1, word_count, fd) < 0)
	{
		return -1;
	}
	(*rt)[word_count] = '\0';
	return word_count;
}

void f_read_line_free(char *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
	}
}