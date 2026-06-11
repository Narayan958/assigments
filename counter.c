

 #include <stdio.h>
 #include <pthread.h>
 
 #define NUM_THREADS  4
 #define INCREMENTS   1000000
 
 
 long long counter_unsafe = 0;   
 long long counter_safe   = 0;   
 pthread_mutex_t lock;           
 
 
 
 
 void *increment_unsafe(void *arg)
 {
     for (int i = 0; i < INCREMENTS; i++)
         counter_unsafe++;          
     return NULL;
 }
 

 void *increment_safe(void *arg)
 {
     for (int i = 0; i < INCREMENTS; i++) {
         pthread_mutex_lock(&lock);  
         counter_safe++;
         pthread_mutex_unlock(&lock); 
     }
     return NULL;
 }
 

 static void run_demo(const char *label,
                      void *(*fn)(void *),
                      long long *counter)
 {
     pthread_t threads[NUM_THREADS];
 
     printf("─────────────────────────────────────────\n");
     printf("%s\n", label);
     printf("Expected : %d\n", NUM_THREADS * INCREMENTS);
 
     for (int i = 0; i < NUM_THREADS; i++)
         pthread_create(&threads[i], NULL, fn, NULL);
 
     for (int i = 0; i < NUM_THREADS; i++)
         pthread_join(threads[i], NULL);
 
     printf("Actual   : %lld  %s\n",
            *counter,
            (*counter == (long long)NUM_THREADS * INCREMENTS)
                ? "✓ correct"
                : "✗ WRONG (race condition)");
 }
 
 
 int main(void)
 {
     printf("\n=== pthread Race Condition vs Mutex Demo ===\n\n");
 
     /* 1. Without mutex */
     run_demo("1) WITHOUT mutex  (race condition)",
              increment_unsafe, &counter_unsafe);
 
     /* 2. With mutex */
     pthread_mutex_init(&lock, NULL);
     run_demo("2) WITH mutex  (correct result)",
              increment_safe, &counter_safe);
     pthread_mutex_destroy(&lock);
 
     printf("─────────────────────────────────────────\n\n");
     return 0;
 }