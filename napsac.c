#include <stdio.h>
#include <time.h>
#define POPULATION_SIZE 50
#define GENE_SIZE 20
#define  MAX_WEIGHT 553
#define MUTATION_RATE 0.05
#define MAX_GENERATION 500

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
void print_all_gene(Individual p[], int p_length);
/* 全ての個体の適応度を計算する関数 */
void calc_fitness(Individual p[], int p_length);
/* ルーレット選択で選択された個体のインデックスを返す関数 */
int selection(Individual p[]);
/* 交叉により子を生成する関数 */
void crossover(int parent1_index, int parent2_index, Individual p[], Individual c[], int i);
/* 突然変異をさせる関数 */
void mutation(Individual p[], int p_length);
/* fitness降順にソートする関数 */
void sort(Individual p[], int p_length);


int main(void){

  int i, j, k;
  Individual population[POPULATION_SIZE];
  Individual childs[POPULATION_SIZE];
  Individual pop_sort[POPULATION_SIZE * 2];
  
  srand((unsigned int) time(0));
  

  initialize(population);

  for(k = 0; k < MAX_GENERATION; k++){
     calc_fitness(population, sizeof(population)/sizeof(population[0]));
//     print_all_gene(population, sizeof(population)/sizeof(population[0]));
     for(i = 0; i < 50 ; i+=2){
       crossover(selection(population), selection(population), population, childs, i);
     }
     calc_fitness(childs, sizeof(childs)/sizeof(childs[0]));
    
     mutation(childs, sizeof(childs)/sizeof(childs[0]));
//     print_all_gene(population, sizeof(population)/sizeof(population[0]));
     for(i = 0; i < POPULATION_SIZE; i++){
       for(j = 0; j < GENE_SIZE; j++){
         pop_sort[i].gene[j] = population[i].gene[j];
       }
       pop_sort[i].fitness = population[i].fitness;
     }
     for(i = 0; i < POPULATION_SIZE; i++){
       for(j = 0; j < GENE_SIZE; j++){
         pop_sort[i+POPULATION_SIZE].gene[j] = childs[i].gene[j];
       }
       pop_sort[i+POPULATION_SIZE].fitness = childs[i].fitness;
     }
    
     calc_fitness(pop_sort, sizeof(pop_sort)/sizeof(pop_sort[0]));
//     printf("sortまえ\n");
//     print_all_gene(pop_sort, sizeof(pop_sort)/sizeof(pop_sort[0]));
     sort(pop_sort, sizeof(pop_sort)/sizeof(pop_sort[0]));
//     printf("sortあと\n");
//     print_all_gene(pop_sort, sizeof(pop_sort)/sizeof(pop_sort[0]));
    
     for(i = 0; i < POPULATION_SIZE; i++){
       for(j = 0; j < GENE_SIZE; j++){
         population[i].gene[j] = pop_sort[i].gene[j];
       }
         population[i].fitness = pop_sort[i].fitness;
     }
    printf("%2d:", 0);
    for(j = 0; j < GENE_SIZE; j++){
      printf("%d ", population[0].gene[j]);
    }
    printf("  fitness:%d\n", population[0].fitness);
   // print_all_gene(population, sizeof(population)/sizeof(population[0]));
  }

  print_all_gene(population, sizeof(population)/sizeof(population[0]));
  return 0;

}

void initialize(Individual p[]){
  int i, j;
  Individual *p_;
  p_ = p;

  for(i = 0; i < POPULATION_SIZE; i++){
    for(j = 0; j < GENE_SIZE; j++){
      p_[i].gene[j] = rand() % 2;
    }
  }
}

/* 全ての集団を出力する関数 */
void print_all_gene(Individual p[], int p_length){
  int i, j;
  Individual *p_;
  p_ = p;

  for(i = 0; i < p_length; i++){
    printf("%2d:", i);
    for(j = 0; j < GENE_SIZE; j++){
      printf("%d ", p_[i].gene[j]);
    }
    printf("  fitness:%d\n", p_[i].fitness);
  }
}

/* 全ての個体の適応度を計算する関数  */
void calc_fitness(Individual p[], int p_length){
  int i, j;
  int f, total_weight;
  Individual *p_;
  p_ = p;
  for(i = 0; i < p_length; i++){
    f = 0;
    total_weight = 0;
    for(j = 0; j < GENE_SIZE; j++){
      if(p_[i].gene[j] == 1){
        f += items.value[j];
        total_weight += items.weight[j];
        if(MAX_WEIGHT < total_weight){
          f = 1;
          break;
        }
      }
    }
    p_[i].fitness = f;
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
    total_fitness += p_[i].fitness;
  }

  rnd = rand() % (total_fitness + 1);
  for(i = 0; i < POPULATION_SIZE; i++){
    tmp += p[i].fitness;
    if(rnd < tmp) break;
  }

  return i;
}

/* 交叉により子を生成する関数 */
void crossover(int parent1_index, int parent2_index, Individual p[], Individual c[], int i){
  int j;
  Individual *p_, *c_;
  p_ = p;
  c_ = c;
  /*
  printf("-----------------------------------------------------------\n");
  printf("parent1 : %2d : ", parent1_index);
  for(j = 0; j < GENE_SIZE; j++) printf("%d ", p_[parent1_index].gene[j]);
  printf("\n");
  printf("parent2 : %2d : ", parent2_index);
  for(j = 0; j < GENE_SIZE; j++) printf("%d ", p_[parent2_index].gene[j]);
  printf("\n");
  */
  int crossover_index = rand() % GENE_SIZE;
//  printf("cross : %2d\n", crossover_index );
  for(j = 0; j < GENE_SIZE; j++){
    if(j < crossover_index){
      c_[i].gene[j] = p_[parent1_index].gene[j];
      c_[i + 1].gene[j] = p_[parent2_index].gene[j];
    }else{
      c_[i].gene[j] = p_[parent2_index].gene[j];
      c_[i + 1].gene[j] = p_[parent1_index].gene[j];
    }
  }
  /*
  printf("child1 :       ", parent1_index);
  for(j = 0; j < GENE_SIZE; j++) printf("%d ", c_[i].gene[j]);
  printf("\n");
  printf("child2 :       ", parent2_index);
  for(j = 0; j < GENE_SIZE; j++) printf("%d ", c_[i + 1].gene[j]);
  printf("\n");
*/
  }

/* 突然変異をさせる関数 */
void mutation(Individual p[], int p_length){
  int i, j, r;
  Individual *p_;
  p_ = p;
  int mutation_r = MUTATION_RATE * 100;

  for(i = 0; i < p_length; i++){
    for(j = 0; j < GENE_SIZE; j++){
      r = rand() % 101;
      if(r < mutation_r){
        if(p[i].gene[j] == 0) p[i].gene[j] = 1; else p[i].gene[j] = 0;
      }
    }
  }
}

/* fitness降順にソートする関数 */
void sort(Individual p[], int p_length){
  int i, j, k;
  Individual tmp;
  for(i = 0; i < p_length; i++){
    for(j = p_length - 1; i < j; j--){
      if(p[j - 1].fitness < p[j].fitness){
        for(k = 0; k < GENE_SIZE; k++){
          tmp.gene[k] = p[j].gene[k];
          p[j].gene[k] = p[j - 1].gene[k];
          p[j - 1].gene[k] = tmp.gene[k];
        }
          tmp.fitness = p[j].fitness;
          p[j].fitness = p[j - 1].fitness;
          p[j - 1].fitness = tmp.fitness;
      }
    }
  }
}
