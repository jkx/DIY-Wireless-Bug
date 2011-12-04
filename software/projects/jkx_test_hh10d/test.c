
#include <stdio.h>

int main()
{
  int f = 6772;

  double RH;
  RH = (0x1E68 - f) * 0x018B / 4096.0;
  printf("%0.2f\n",RH);    


  int RH1;
  RH1 = (0x1E68 - f) * 0x018B / 4096.0;
  printf("%d\n",RH1);    

  return 0;
}
