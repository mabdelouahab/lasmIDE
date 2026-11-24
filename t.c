// t.c   gcc -O0 -fno-omit-frame-pointer -c t.c -o t.o
#include <stdint.h>
#include <stdarg.h>
#define AL16 ((((uintptr_t)__builtin_frame_address(0)) & 15) == 0)
#define D(i) ((i) + 0.5)

int t_i6(long a,long b,long c,long d,long e,long f)
{ return !(AL16&&a==1&&b==2&&c==3&&d==4&&e==5&&f==6); }
int t_i7(long a,long b,long c,long d,long e,long f,long g)
{ return !(AL16&&a==1&&b==2&&c==3&&d==4&&e==5&&f==6&&g==7); }
int t_i8(long a,long b,long c,long d,long e,long f,long g,long h)
{ return !(AL16&&a==1&&b==2&&c==3&&d==4&&e==5&&f==6&&g==7&&h==8); }
int t_i9(long a,long b,long c,long d,long e,long f,long g,long h,long i)
{ return !(AL16&&a==1&&b==2&&c==3&&d==4&&e==5&&f==6&&g==7&&h==8&&i==9); }

int t_d8(double a,double b,double c,double d,double e,double f,double g,double h)
{ return !(AL16&&a==D(1)&&b==D(2)&&c==D(3)&&d==D(4)&&e==D(5)&&f==D(6)&&g==D(7)&&h==D(8)); }
int t_d9(double a,double b,double c,double d,double e,double f,double g,double h,double i)
{ return !(AL16&&a==D(1)&&b==D(2)&&c==D(3)&&d==D(4)&&e==D(5)&&f==D(6)&&g==D(7)&&h==D(8)&&i==D(9)); }
int t_d10(double a,double b,double c,double d,double e,double f,double g,double h,double i,double j)
{ return !(AL16&&a==D(1)&&b==D(2)&&c==D(3)&&d==D(4)&&e==D(5)&&f==D(6)&&g==D(7)&&h==D(8)&&i==D(9)&&j==D(10)); }

/* 7 صحيحة + 9 float بترتيب متداخل: g و x9 على المكدس */
int t_mix(long a,double x1,long b,double x2,long c,double x3,long d,double x4,
          long e,double x5,long f,double x6,long g,double x7,double x8,double x9)
{ return !(AL16&&a==1&&b==2&&c==3&&d==4&&e==5&&f==6&&g==7
        &&x1==D(1)&&x2==D(2)&&x3==D(3)&&x4==D(4)&&x5==D(5)&&x6==D(6)&&x7==D(7)&&x8==D(8)&&x9==D(9)); }

/* متغيّرة المعاملات: تفشل إن كان AL خاطئًا */
int t_va(int n, ...)
{ va_list ap; va_start(ap,n); int bad=!AL16;
  for(int i=1;i<=n;i++) if(va_arg(ap,double)!=D(i)) bad=1;
  va_end(ap); return bad; }

/* أحجام مختلفة */
int t_sz(char a,short b,int c,long d,float e,double f)
{ return !(AL16&&a==1&&b==2&&c==3&&d==4&&e==D(5)&&f==D(6)); }

/* نصوص تحوي فاصلة و! */
int t_str(const char *s,const char *t)
{ int i=0; const char *e="a,bc<d>"; for(;e[i]&&s[i]==e[i];i++); 
  return !(AL16 && !e[i] && t[0]=='\n' && t[1]==0); }
