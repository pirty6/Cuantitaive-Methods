#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define CUSTOMERS 30000
#define MAX_CAPACITY 1200

int main(){
  srand(time(NULL));
  double arriving_time[CUSTOMERS] = {0};
  double arriving_turnstiles[CUSTOMERS] = {0};
  double leaving_turnstiles[CUSTOMERS] = {0};
  double waiting_time[CUSTOMERS] = {0};
  double turnstiles_time;
  int lambda = 100, lambda_turnstiles = 60, train_departure = 10, i, flag = 1;
  int  total_waiting = 0, waiting_people = 0, people_queue_train=0, people_train;

  arriving_turnstiles[0] = arriving_time[0] = (-1.0/lambda) * log(rand() * 1.0 / RAND_MAX);
  leaving_turnstiles[0] = arriving_turnstiles[0] + (-1.0 / lambda_turnstiles) * log(rand() * 1.0 / RAND_MAX);


  for (i = 1; i < CUSTOMERS; i++) {
    if(arriving_time[i - 1] > 60) {
        lambda = (arriving_time[i - 1] < 120) ? 175 : 135;
        lambda_turnstiles = 140;
    }

    arriving_time[i] = (-1.0/lambda) * log(rand() * 1.0 / RAND_MAX)+arriving_time[i-1];
    arriving_turnstiles[i] = ( arriving_time[i] > leaving_turnstiles[i - 1]) ? arriving_time[i] : leaving_turnstiles[i - 1];
    turnstiles_time = (-1.0 / lambda_turnstiles) * log(rand() * 1.0 / RAND_MAX);
    leaving_turnstiles[i] = arriving_turnstiles[i] + turnstiles_time;
  }


  for (i = 0; i < CUSTOMERS; i++){

    if(leaving_turnstiles[i] > train_departure || people_queue_train >= 1200){
        people_train = (people_queue_train < 1200)? people_queue_train : 1200;
        people_queue_train = (people_queue_train - MAX_CAPACITY>0)? people_queue_train - MAX_CAPACITY : 0;
        train_departure += 10;
      }

    if( (leaving_turnstiles[i] >= 60 && (flag & 0b1)) || (leaving_turnstiles[i] >= 120 && (flag & 0b10))){
        printf("Waiting time between  %i pm and %i pm %f\n\n", flag+3, flag+4, total_waiting * 1.0 / waiting_people);
        flag = flag << 1;
        total_waiting = 0;
        waiting_people = 0;
    }

    waiting_time[i] = train_departure - arriving_time[i];
    total_waiting += waiting_time[i];
    waiting_people ++;
    people_queue_train ++;
  }


  if (people_queue_train > 0) {
    people_train = (people_queue_train < 1200)? people_queue_train : 1200;
    people_queue_train = (people_queue_train - MAX_CAPACITY>0) ? people_queue_train - MAX_CAPACITY : 0;
    train_departure += 10;
  }

  printf("Waiting time after 7 pm: %f \n\n", total_waiting * 1.0 / waiting_people);
}
