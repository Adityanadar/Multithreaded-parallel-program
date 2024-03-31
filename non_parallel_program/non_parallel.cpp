/* creating a non parallel program to compute a methematical operation
mathemtical function gamma[i] = (alpha[i]^ beta[i])%p is calculated here
no multithreading is employed in this program
Execution time:  ~3 sec 
*/

#include <iostream>
#include <thread>
#include <bits/stdc++.h>
#include <chrono>

using namespace std;

long powerFunction(long a, long b, long p){
    long res = 1;
    long i = 0;
    while (i<b)
    {
        res*=a;
        res%=p;
        ++i;
    }
    return res;
}

void non_parallel_function(long* alpha, long* beta, long* gamma, long p, long n){
    long i = 0;
    while(i<n){
        gamma[i] = powerFunction(alpha[i], beta[i], p);
        ++i;
    }

}

int main()
{
    //clock_t start,end;
    //start = clock();
    cout<<"Starting execution...\n";
    long * alpha, * beta, * gamma;
    long p=17;
    long N=100000;
    alpha=new long[N]; beta=new long[N]; gamma=new long[N];
    alpha[0]=8;beta[0]=5183;alpha[1]=9;beta[1]=4351;
    alpha[2]=7;beta[2]=4711;
    long i=3;
    while(i < N){
        alpha[i]=alpha[i-3];beta[i]=beta[i-3];++i;
    }

    auto start = chrono::high_resolution_clock::now();
    // unsync the I/O of C and C++.
    ios_base::sync_with_stdio(false);

    non_parallel_function(alpha,beta,gamma,p,N);
    //thread th1(thread_function1, 100000);
    //th1.join();
    //end = clock();
    auto end = chrono::high_resolution_clock::now();
    
    // Calculating total time taken by the program.
    double time_taken = 
      chrono::duration_cast<chrono::nanoseconds>(end - start).count();
 
    time_taken *= 1e-9;
 
    cout << "Time taken by program is : " << fixed 
         << time_taken << setprecision(9);
    cout << " sec" << endl;
    
    // first few terms of the sequence
    for(long i=0;i<100;++i){
        cout<<gamma[i]<<"\t";
        if(i%10==9){std::cout<<"\n";}
    }
    cout<<"\n";
    delete[] alpha;delete[] beta;delete[] gamma;
    return 0;
   
}