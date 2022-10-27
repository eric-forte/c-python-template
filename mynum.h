#ifndef __MYNUM_H__
#define __MYNUM_H__

/* mynum struct */
typedef struct {
    int num;
    char* desc;
} Mynum;

int my_add(int input_one, int input_two);
Mynum* get_mynum(int in_num, char* in_desc);
void free_mynum(Mynum* mynum);
void print_mynum(Mynum mynum);
void print_mynum_pointer(Mynum* mynum);


#endif /* __mynum_H__ */
