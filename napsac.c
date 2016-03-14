#include <stdio.h>
#include <time.h>
#define POPULATION_SIZE 50
#define GENE_SIZE 20
#define  MAX_WEIGHT 553
#define WEIGHT 0
#define PROFIT 1

typedef struct{
  int weight[20]; //重量
  int value[20]; //価値
} Items;

Items items = {
  {20, 80, 49, 95, 68, 32, 100, 69, 65, 73, 18, 44, 25, 37, 90, 75, 11, 83, 15, 57},
  {32, 52, 69, 42, 19, 12,  39, 72, 35, 74, 96, 24, 82, 82, 84, 60, 73, 100, 88, 56}
};

typedef struct{
  int gene[20];
  int fitness;
} Individual;

void initialize(Individual p[]);
/* 全ての集団を出力する関数 */
void print_all_gene(Individual p[]);
/* 全ての個体の適応度を計算する関数 */
void calc_fitness(Individual p[]);
/* ルーレット選択で選択された個体のインデックスを返す関数 */
int selection(Individual p[]);

int main(void){

  int i, j;
  Individual population[POPULATION_SIZE];
  
  srand((unsigned int) time(0));
  

  initialize(population);
  calc_fitness(population);
  print_all_gene(population);

  printf("%d\n", selection(population));
  printf("%d\n", selection(population));

  
  /*

  int childs[POPULATION_SIZE][GENE_SIZE];
  for(i = 0; i < POPULATION_SIZE; i += 2){
    int parent1_index = selection(population, fitness);
    int parent2_index = selection(population, fitness);
    printf("parent1 : %2d : ", parent1_index);
    for(j = 0; j < GENE_SIZE; j++) printf("%d ", population[parent1_index][j]);
    printf("\n");
    printf("parent2 : %2d : ", parent2_index);
    for(j = 0; j < GENE_SIZE; j++) printf("%d ", population[parent2_index][j]);
    printf("\n");
    int crossover_index = rand() % GENE_SIZE;
    int child1[GENE_SIZE];
    int child2[GENE_SIZE];
    for(j = 0; j < GENE_SIZE; j++){
      if(j < crossover_index){
        childs[i][j] = population[parent1_index][j];
        childs[i + 1][j] = population[parent2_index][j];
      }else{
        childs[i][j] = population[parent2_index][j];
        childs[i + 1][j] = population[parent1_index][j];
      }
    }
    printf("child1 :       ", parent1_index);
    for(j = 0; j < GENE_SIZE; j++) printf("%d ", childs[i][j]);
    printf("\n");
    printf("child2 :       ", parent2_index);
    for(j = 0; j < GENE_SIZE; j++) printf("%d ", childs[i + 1][j]);
    printf("\n");
  }
  */

}

void initialize(Individual p[]){
  int i, j;
  Individual *p_;
  p_ = p;

  for(i = 0; i < POPULATION_SIZE; i++){
    for(j = 0; j < GENE_SIZE; j++){
      p_->gene[j] = rand() % 2;
    }
    p_++;
  }
}

/* 全ての集団を出力する関数 */
void print_all_gene(Individual p[]){
  int i, j;
  Individual *p_;
  p_ = p;

  for(i = 0; i < POPULATION_SIZE; i++){
    printf("%2d:", i);
    for(j = 0; j < GENE_SIZE; j++){
      printf("%d ", p_->gene[j]);
    }
    printf("  fitness:%d\n", p_->fitness);
    //printf("\n");
    p_++;
  }
}

/* 全ての個体の適応度を計算する関数  */
void calc_fitness(Individual p[]){
  int i, j;
  int f, total_weight;
  Individual *p_;
  p_ = p;
  for(i = 0; i < POPULATION_SIZE; i++){
    f = 0;
    total_weight = 0;
    for(j = 0; j < GENE_SIZE; j++){
      if(p_->gene[j] == 1){
        f += items.value[j];
        total_weight += items.weight[j];
        if(MAX_WEIGHT < total_weight){
          f = 1;
          break;
        }
      }
    }
    p_->fitness = f;
    p_++;
  }
}

/* ルーレット選択で選択された個体のインデックスを返す関数 */
int selection(Individual p[]){
  int i, j, rnd;
  int total_fitness = 0;
  int tmp = 0;
  Individual *p_;
  p_ = p;
  for(i = 0; i < POPULATION_SIZE; i++){
    total_fitness += p_->fitness;
    p_++;
  }

  rnd = rand() % (total_fitness + 1);
  p_ = p;
  for(i = 0; i < POPULATION_SIZE; i++){
    tmp += p->fitness;
    if(rnd < tmp) break;
    p_++;
  }

  return i;
}
