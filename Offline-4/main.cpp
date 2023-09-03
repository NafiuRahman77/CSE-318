#include <bits/stdc++.h>
#include <cmath>
#include "dataset.hpp"
#include "decision_tree.hpp"
#include "car.hpp"

using namespace std;

int main()
{
    std::ifstream inputFile("car.data");
    if (!inputFile.is_open())
    {
        std::cerr << "Error opening file." << std::endl;
        return 1;
    }

    std::vector<Car> cars; // Assuming you want to store multiple cars
    int c = 0;
    std::string line;
    while (std::getline(inputFile, line))
    {
        // cout<<c++<<endl;
        std::istringstream iss(line);
        std::string token;

        Car car;

        for (int i = 0; i < Car::attribute_count; ++i)
        {
            if (std::getline(iss, token, ','))
            {
                car.attribute_values_string.push_back(token);
                // cout<<token<<endl;
            }
            else
            {
                std::cerr << "Error parsing attribute value." << std::endl;
                return 1;
            }
        }

        if (std::getline(iss, car.verdict_string))
        {
            // cout<<car.verdict_string<<endl;
            cars.push_back(car); // Store the car object in the vector
        }
        else
        {
            std::cerr << "Error parsing verdict." << std::endl;
            return 1;
        }
        // cout<<"bop"<<endl;
    }
    // cout<<"bnuku"<<endl;
    cout << cars.size() << endl;
    for (int i = 0; i < cars.size(); i++)
    {

        cars[i].map_to_int();
    }

    inputFile.close();

    // dt.learn(cars,v,{});
    // cout<<dt.infer(cars[0])<<endl;
    // cout<<dt.infer(cars[1])<<endl;
    // cout<<dt.infer(cars[2])<<endl;
    // cout << cars[0].verdict << endl;
    // cout << cars[1].verdict << endl;
    // cout << cars[2].verdict << endl;

    double accuracy_sum = 0;
    double mean_accuracy;
    vector<double> means;

    for (int i = 0; i < 20; i++)
    {
        cout << i << endl;
        random_device rd;
        mt19937 g(rd());
        shuffle(cars.begin(), cars.end(), g);
        size_t totalSize = cars.size();
        size_t splitpoint = static_cast<size_t>(totalSize * 0.8);
        vector<Car> train_set(cars.begin(), cars.begin() + splitpoint);
        vector<Car> test_set(cars.begin() + splitpoint, cars.end());

        vector<bool> v(6, true);
        DecisionTree dt;
        int match = 0;
        dt.learn(train_set, v, {});
        for (int i = 0; i < test_set.size(); i++)
        {
            int res = dt.infer(test_set[i]);
            if (res == test_set[i].verdict)
            {
                match++;
            }
        }
        accuracy_sum += (double)match / test_set.size();
        means.push_back((double)match / test_set.size());
        cout << (double)match / test_set.size() << endl;
        ;
    }
    mean_accuracy = accuracy_sum / 20;
    cout << "Mean accuracy: " << mean_accuracy * 100 << endl;

    double std_dev;
    double xminusmu;
    double sum = 0.0;
    double sum_squared = 0.0;
    int n = means.size();

    for (int i = 0; i < n; ++i)
    {
        sum += means[i];
        sum_squared += means[i] * means[i];
    }

    double variance = (sum_squared / n) - (sum / n) * (sum / n);

    double standard_deviation = std::sqrt(variance);
    cout << "Standard Deviation: " << standard_deviation * 100 << endl;

    return 0;
}