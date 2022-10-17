#include <iostream> // terminal input-output
#include <random> // random numbers
#include <fstream> // files input-output
#include <cmath>
#include<vector>

void box_muller(double mu, double sigma, int N, double array[]) {
    /* This function generates an array of N normally distributed random numbers from 
    a uniform distribution of random numbers using the box-müller transform. */

    std::random_device seed; // generate a random seed (random integer)
    std::mt19937 generator(seed()); // initialise mt19937 random number generator with the seed
    std::uniform_real_distribution<float> uniform(0, 1); // function to generate a uniform real random number between 0 and 1
    int i;
    double uniform_1;
    double uniform_2;
    double pi = acos(-1);

    for (int i = 0; i < N/2; i++) {
        uniform_1 = uniform(generator);
        uniform_2 = uniform(generator);
        array[i] = sigma*sqrt(-2*log(uniform_1))*cos(2*pi*uniform_2)+mu;
        array[i+N/2] = sigma*sqrt(-2*log(uniform_1))*sin(2*pi*uniform_2)+mu;
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

double metric(double x, double x_0, double y, double y_0) {
    /* This function calculates distance between two points 
    in the plane (x,y) (x_0,y_0)*/

    return sqrt(pow((x-x_0),2) + pow((y-y_0),2));
}

int main() {

//  VARIABLES ----------------------------------------------------------

    std::random_device seed; // generate a random seed (random integer)
    std::mt19937 generator(seed()); // initialise mt19937 random number generator with the seed
    std::uniform_real_distribution<float> uniform_one(-1, 1); // function to generate a uniform real random number between 0 and 1
    
    const int N = 10e4; // number of random numbers to generete
    double normal[N]; // array for the random numbers
    std::uniform_int_distribution<> rand_int(0, N); // generate a uniformly distributed random integer number between 0 and N
    
    std::uniform_int_distribution<> epsilon(0, 1); // generate a uniformly distributed random integer number between 0 and 1

    std::ofstream file;
    
    double dt = 1;
    int t_steps[] = {1,3,10,30,50,70,90,100,0};
    int n = sizeof(t_steps) / sizeof(*t_steps); // size of t_steps
    t_steps[n-1] = t_steps[n-2]+1;
    
    int L = 100; // size of the box
    double Gamma = 1; // amplitude of the noise

    int M = 1000; // number of particles

    double f[] = {1,0.1,0.01,0.001}; // force amplitude

    box_muller(0,1,N,normal); 

    file.open("data_6.dat"); 

    // coord. without PBC and initial conditions 0
    std::vector< std::vector<double> > x_out(t_steps[n-1]+1, std::vector<double> (M, 0)); // (extra t step for proper loop calculation)

    for (int r = 0; r < sizeof(f)/sizeof(*f); r++) {

        for (int t = 0; t < t_steps[n-1]; t++) { 

            for (int j = 0; j < M; j++) {
                // next step
                x_out[t+1][j] = f[r]*(2*epsilon(generator)-1) + sqrt(2*Gamma*dt)*normal[rand_int(generator)]+x_out[t][j];
            }        
            
            // calculate the Mean-Square Displacement for x coord.
            double MSD = 0;
            for (int i = 0; i < M; i++) {
                MSD += pow(x_out[t][i],2);
            }
            MSD = MSD/M;
            file << t << ' ' << MSD/2 << '\n';
        
        }

        file << '\n';
        file << '\n';

    }

    file.close();

    system("gnuplot figure_6.gnu");

    return 0;
}


