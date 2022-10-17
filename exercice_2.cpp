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

void histograma(int N, std::vector<double> &data, double min, double max, double n_box, std::vector<double> &bin, std::vector<double> &hist) {
    /* This function generates a histogram form a set of data */
    int i_count = 0;
    int i_box = 0;
    double box_size = (max-min)/n_box;
    bin.resize(n_box);
    hist.resize(n_box);
    std::fill(bin.begin(), bin.end(), 0);
    std::fill(hist.begin(), hist.end(), 0);
    for (int i=0; i<N; i++) {
        if(min < data[i] & data[i] < max) {
            i_box = int((data[i]-min)/box_size);
            hist[i_box] += 1;
            i_count += 1;
        }
    }
    for (int i=0; i < n_box; i++) {
        bin[i] = min + box_size/2 + i*box_size;
        hist[i] = hist[i]/i_count/box_size;
    }
}

double exp_val(std::vector<double> &data) {
    /* This function calculates the expected value of a set of data */
    double mean = 0;
    for(int i=0; i<data.size(); i++) {
        mean += data[i];
    }
    return mean/data.size();
}

double std_dev(std::vector<double> &data) {
    /* This function calculates the standard deviation of a set of data */
    double mean = 0;
    for(int i=0; i<data.size(); i++) {
        mean += data[i];
    }
    mean = mean/data.size();
    double stddev = 0;
    for(int i=0; i<data.size(); i++) {
        stddev += pow(data[i]-mean,2);
    }
    return sqrt(stddev/data.size());
}

int main() {

    // Generation of N normally distributed ranodm numbers with mean 0 and standard deviation 1
    int N = 10e4; // number of random numbers to generete
    std::vector<double> normal; // vector for the random numbers
    box_muller(0,1,N,normal);

    // Numerical calculus of the mean value and variance of the data
    double mean;
    mean = exp_val(normal);
    std::cout << "mean = ";
    std::cout << mean << '\n';
    double standard_deviation;
    standard_deviation = std_dev(normal);
    std::cout << "stand. dev. = ";
    std::cout <<  standard_deviation << '\n';

    // Generate and plot distribution
    double min = -6, max = 6;
    double box_size = 0.2;
    int n_box = int((max-min)/box_size);
    std::vector<double> prob;
    std::vector<double> box;
    histograma(N,normal,-20,20,n_box,box,prob);
    std::ofstream file;
    file.open("data_1.dat");  
    for (int i = 0; i < n_box; i++) {
        file << box[i] << ' ' << prob[i] << '\n';
    }
    file.close();
    system("gnuplot figure_1.gnu");

    return 0;
}


