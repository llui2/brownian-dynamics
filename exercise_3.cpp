#include <iostream> // terminal input-output
#include <random> // random numbers
#include <fstream> // files input-output

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

int main() {
    
    // Generation of N normally distributed ranodm numbers with mean 0 and standard deviation 1
    int N = 10e4; // number of random numbers to generete
    std::vector<double> normal; // vector for the random numbers
    box_muller(0,1,N,normal); 

    std::random_device seed; // generate a random seed (random integer)
    std::mt19937 generator(seed()); // initialise mt19937 random number generator with the seed
    std::uniform_int_distribution<> rand_int(0, N); // generate a uniformly distributed random number between 0 and N
    double dt = 0.1; // time step
    int t_steps = 100; // total number of time steps
    double T = t_steps*dt; // total evolution time
    double Gamma = 1; // amplitude of the noise
    std::vector<double> x(t_steps,0), y(t_steps,0); // particle coordinates with (x_0,y_0)=(0,0)

    // Calculate trajectory
    for (int i = 0; i < t_steps-1; i++) { 
        x[i+1] = sqrt(2*Gamma*dt)*normal[rand_int(generator)]+x[i];
        y[i+1] = sqrt(2*Gamma*dt)*normal[rand_int(generator)]+y[i];
    }

    // Plot trajectory
    std::ofstream file;
    file.open("data_2.dat");  
    for (int i = 0; i < t_steps; i++) {
        file << x[i] << ' ' << y[i] << '\n';
    }
    file.close();
    system("gnuplot figure_2.gnu");

    return 0;
}