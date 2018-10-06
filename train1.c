#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>

int customers = 40000;
double lambda_turnstiles = 100;
double miu_turnstiles = 60;
double miu_train = 120;


int main() {
  int i;
  double* a_time = malloc(customers * sizeof(double));
  double* s_time = malloc(customers * sizeof(double));
  double* s_start = malloc(customers * sizeof(double));
  double* s_ends = malloc(customers * sizeof(double));
  double* train_s_time = malloc(customers * sizeof(double));
  double* train_s_ends = malloc(customers * sizeof(double));
  double* w = malloc(customers * sizeof(double));
  double w1 = 0, w2 = 0, w3 = 0;
  int c1 = 0, c2 = 0, c3 = 0;

  srand(time(0));

  for(i = 0; i < customers; i++) {
    if(i == 0){
      a_time[0] = 0;
      s_start[0] = 0;
    }
    if(a_time[i-1] >= 60 && a_time[i-1] < 120) {
      lambda_turnstiles = 175;
      c2++;
      miu_turnstiles = 140;
    }
    if(a_time[i-1] >= 120) {
      lambda_turnstiles = 135;
      c3++;
    }
    a_time[i] = a_time[i-1] - (1/lambda_turnstiles) *log(rand() * 1.0 / RAND_MAX);
    s_start[i] = a_time[i] > s_ends[i-1] ? a_time[i] : s_ends[i-1];
    s_time[i] = (-1.0/miu_turnstiles) * log(rand() * 1.0 / RAND_MAX);
    s_ends[i] = s_time[i] + s_start[i];

    train_s_time[i] = (-1.0/miu_train) * log(rand() * 1.0 / RAND_MAX);
    train_s_ends[i] = train_s_time[i] + s_ends[i];
    w[i] = train_s_ends[i] - a_time[i];
    
  }
  c1 = customers - (c2 + c3);
  for(i = 0; i < customers; i++) {
    if(i < c1) {
      w1 += w[i];
    }
    if(i >= c1 && i < c1+c2) {
      w2+=w[i];
    } else {
      w3 +=w[i];
    }
  }

  w1 /= c1;
  w2 /= c2;
  w3 /= c3;
  printf("w1 %lf, w2 %lf, w3 %lf\n", w1, w2, w3);
  return 0;
}
