#include <iostream> // terminal input-output
#include <random> // random numbers
#include <fstream> // files input-output
#include <cmath>
#include<vector>

void box_muller(double mu, double sigma, int N, std::vector<double> &array) {
    /* This function generates an array of N normally distributed random numbers from 
    a uniform distribution of random numbers using the box-müller transform. */

    std::random_device seed; // generate a random seed (random integer)
    std::mt19937 generator(seed()); // initialise mt19937 random number generator with the seed
    std::uniform_real_distribution<float> uniform(0, 1); // function to generate a uniform real random number between 0 and 1
    double uniform_1;
    double uniform_2;
    double pi = acos(-1);

    for (int i = 0; i < N/2; i+=1) {
        uniform_1 = uniform(generator);
        uniform_2 = uniform(generator);
        array.push_back(sigma*sqrt(-2*log(uniform_1))*cos(2*pi*uniform_2)+mu);
        array.push_back(sigma*sqrt(-2*log(uniform_1))*sin(2*pi*uniform_2)+mu);
    }
}

int sign(float x){
    /* This function is equivalent to the sing(x) math function,
    returns +1 if x is positive and -1 if x is negative. */

    if (signbit(x)) {
        return 1;
    }
    else {
        return -1;
    }
}

int main() {

    // Generation of N normally distributed ranodm numbers with mean 0 and standard deviation 1
    int N = 10e4; // number of random numbers to generete
    std::vector<double> normal; // vector for the random numbers
    box_muller(0,1,N,normal); 

    std::random_device seed; // generate a random seed (random integer)
    std::mt19937 generator(seed()); // initialise mt19937 random number generator with the seed
    std::uniform_int_distribution<> rand_int(0, N); // generate a uniformly distributed random number between 0 and N
    std::uniform_real_distribution<float> uniform_one(-1, 1); // function to generate a uniform real random number between 0 and 1

    double dt = 0.1; // time step
    int t_steps[] = {1,3,10,30,100,1000,0}; // total number of time steps
    int n = sizeof(t_steps) / sizeof(*t_steps); // number of different t_steps to save
    t_steps[n-1] = t_steps[n-2]+1;
    double Gamma = 1; // amplitude of the noise
    int M = 1000; // number of particles
    std::vector< std::vector<double> > x_out(t_steps[n-1]+1, std::vector<double> (M, 0)); // coordinates

    // Sample the displacement of the distribution
    std::ofstream file;
    file.open("data_5.dat");     
    for (int t = 0; t < t_steps[n-1]; t++) {
        for (int j = 0; j < M; j++) {
            // next step
            x_out[t+1][j] = sqrt(2*Gamma*dt)*normal[rand_int(generator)]+x_out[t][j];
        }        
        // save position at desired times
        bool save = std::find(t_steps, t_steps + n, t) != t_steps + n;
        if (save) {    
        for (int k = 0; k < M; k++) {   
            file << x_out[t][k] << '\n';
        }  
        file << " \n";
        file << " \n";
        }
    }
    file.close();

    system("gnuplot figure_5.gnu");

    return 0;
}


