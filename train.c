#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <math.h>

int population = 40000;
double lambda[3] = {6000, 10500, 8100}, miuT = 3600;
double timePassed = 0;

int main(int argc, char* argv[]) {
  srand(time(0));
  int i = 0, i_break;
  int currentLambda = 0;
  double aTime = 0;
  double ssTime = 0;
  double sstart = 0, sends = 0, w=0, wq, w1=0, w2=0, w3=0, this_time;

  for(i = 0; i < population; i++) {
    if(timePassed >= 60 && currentLambda < 2) {
      currentLambda++;
    }
    if(timePassed > 2*60){
      miuT = 4800;
    }
    // printf("timePassed = %lf, Wq = %lf\n", timePassed, wq);
    if(i != 0) {
      aTime = aTime - ((1/lambda[currentLambda]) * log((rand() + 1.0) / (RAND_MAX+2.0)));
      if(sends < aTime){
        sstart = aTime;
      }else{
        sstart = sends;
      }
    }
    ssTime = (1/miuT) * log(rand());
    sends= ssTime + sstart;
    // printf("aTime: %lf, ssTime: %lf, sends: %lf, sstart: %lf, Lambda: %.1lf\n", aTime, ssTime, sends, sstart, lambda[currentLambda]);
    w = sends - aTime;
    wq = sstart - aTime;
    timePassed += w;
    if(currentLambda == 0){
      i_break = i + 1;
      w1 = timePassed / i_break;
      this_time = timePassed;
    }
    if (currentLambda == 1){
      w2 = (timePassed - this_time) / (i + 1 - i_break);
      this_time = timePassed;
      i_break = i + 1;
    }
    if (currentLambda == 2){
      w3 = (timePassed - this_time) / (i + 1 - i_break);
      this_time = timePassed;
    }
    printf("timePassed %lf, this_time %lf, i %i, i_break %i\n", timePassed, this_time, i, i_break);
    // printf("W = %lf, Wq = %lf\n", w, wq);
  }
  printf("w1 %lf, w2 %lf, w3 %lf\n", w1, w2, w3);
  return 0;
}
