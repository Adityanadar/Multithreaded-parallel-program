/* creating a parallel program to compute a methematical operation
mathemtical fucntion gamma[i] = (alpha[i]^ beta[i])%p is calculated here
thread::hardware_concurrency gives ideal number of threads to speed up the process
performance improvement noted: from ~3 sec to 0.802 secs , from non parallel to parallel program
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

void execute_one_thread(long* alpha, long* beta, long* gamma, long p, long m, long start, long end){
    while(start < end){
        gamma[start] = powerFunction(alpha[start], beta[start], p);
        start+= m;
    }
}

void parallel_function(long* alpha, long* beta, long* gamma, long p, long n, long m){
    if (m<1){
        m = 1;
    }
    thread* allTh;
    allTh = new thread[m];
    for (long i=0; i<m; ++i){
        allTh[i] = thread(execute_one_thread, alpha, beta, gamma, p, m, i, n);
    }
    for(long i=0;i<m;++i){
        allTh[i].join();
    }
    delete[] allTh;

}


int main()
{
    //num_threads = 3;
    long m = thread::hardware_concurrency();
    cout<<"Starting execution with threads... "<< m << "\n";
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

    parallel_function(alpha, beta, gamma, p, N, m);
    
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