/**
 * File: Generic Print
 *
 * Copyright 2021 Exebook
 * MIT License
 */
#ifndef CPY_PRINT_H
#define CPY_PRINT_H


extern int __print_enable_color;
void __print_color(FILE *fd, int a);

#define __print_array(fd, T, qual, color)                 \
  __print_color(fd, __print_color_normal);                \
  int max_len = 16;                                       \
  int n = size / sizeof(T);                               \
  T *m = va_arg(v, T *);                                  \
  fprintf(fd, "[");                                       \
  __print_color(fd, color);                               \
  for (int i = 0; i < (n < max_len ? n : max_len); i++) { \
    if (i > 0) fprintf(fd, " ");                          \
    fprintf(fd, qual, m[i]);                              \
  }                                                       \
  __print_color(fd, __print_color_normal);                \
  if (n > max_len) fprintf(fd, "...");                    \
  fprintf(fd, "]");

extern int __print_color_normal;  // -1 means default terminal foreground color
extern int __print_color_number;
extern int __print_color_string;
extern int __print_color_hex;
extern int __print_color_float;

void __print_setup_colors(int normal, int number, int string, int hex,
                          int fractional);
void __print_func(FILE *fd, int count, unsigned short types[], ...);

// clang-format off
#define __print_typeid(a) \
	__builtin_choose_expr(__print_is_type(a, List*), List_t, \
	__builtin_choose_expr(__print_is_type(a, bool), Bool_t, \
	__builtin_choose_expr(__print_is_type(a, double), Double_t, \
	__builtin_choose_expr(__print_is_type(a, double*), DoubleList_t, \
	__builtin_choose_expr(__print_is_type(a, float), Float_t, \
	__builtin_choose_expr(__print_is_type(a, char), Char_t, \
	__builtin_choose_expr(__print_is_type(a, unsigned char), Uchar_t, \
	__builtin_choose_expr(__print_is_type(a, int), Int_t, \
	__builtin_choose_expr(__print_is_type(a, unsigned int), Uint_t, \
	__builtin_choose_expr(__print_is_type(a, long), Long_t, \
	__builtin_choose_expr(__print_is_type(a, unsigned long), Ulong_t, \
	__builtin_choose_expr(__print_is_type(a, short), Short_t, \
	__builtin_choose_expr(__print_is_type(a, char*), Str_t, \
	__builtin_choose_expr(__print_is_type(a, char[]), CharArray_t, \
	__builtin_choose_expr(__print_is_type(a, void*), Void_t, \
	__builtin_choose_expr(__print_is_type(a, double[]), DoubleArray_t, \
	__builtin_choose_expr(__print_is_type(a, unsigned int[]), UintArray_t, \
	__builtin_choose_expr(__print_is_type(a, short[]), ShortArray_t, \
	__builtin_choose_expr(__print_is_type(a, unsigned short[]), UshortArray_t, \
	__builtin_choose_expr(__print_is_type(a, char*[]), StrArray_t, \
	__builtin_choose_expr(sizeof(a) == 1, 2, \
	__builtin_choose_expr(sizeof(a) == 2, 4, \
	(0)  ))))))))))))))))))))))

#define __print_push(c,size,cont) (cont, *--_p = c | (size << 5))
#define __builtin_choose_expr __builtin_choose_expr
#define __print_is_type(a, t) __builtin_types_compatible_p(typeof(a), t)
#define __print_count_int(q,w,e,r,t,y,u,i,o,p,a,s,d,f,g,h,j,k,l,z,x,c,v,b,n,m,...) m
#define __print_count(a...)__print_count_int(a,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0)

#define __print_code(a, cont) __builtin_choose_expr(__print_is_type(a, void), 0, __print_push(__print_typeid(a), (sizeof(a)<(1<<16>>5)?sizeof(a):(1<<16>>5)-1), cont))

#define __print_types_int(q,w,e,r,t,y,u,i,o,p,a,s,d,f,g,h,j,k,l,z,x,c,v,b,n,m,...)__print_code(q,__print_code(w,__print_code(e,__print_code(r,__print_code(t,__print_code(y,__print_code(u,__print_code(i,__print_code(o,__print_code(p,__print_code(a,__print_code(s,__print_code(d,__print_code(f,__print_code(g,__print_code(h,__print_code(j,__print_code(k,__print_code(l,__print_code(z,__print_code(x,__print_code(c,__print_code(v,__print_code(b,__print_code(n,__print_code(m, 0))))))))))))))))))))))))))

// NOLINTNEXTLINE
#define __print_types(a...) __print_types_int(a, (void)0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1)

// clang-format on
// If you remove the ({}), then reclaration error appears!
#define fprint(fd, a...)                              \
  ({                                                  \
    int count = __print_count(a);                     \
    unsigned short stack[count], *_p = stack + count; \
    (void)__print_types(a);                                 \
    (void)__print_func(fd, count, _p, a);                   \
  })

#define print(a...) (void)fprint(stdout, a);

#endif
