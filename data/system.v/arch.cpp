//system.v arch.


#include <iostream>

class AutonomousCar {
public:

    void navigateToDestination(int destination) {
        for (int i = 0; i < destination; ++i) {
           std::cout << "Moving to waypoint " << i + 1 << std::endl;
                  simulateComputation();
        }
        std::cout << "Destination reached!" << std::endl;
    }

private:
   
    void simulateComputation() {
        for (int i = 0; i < 1000000; ++i) {
            // Simulate computation
        }
    }
};

int main() {
    AutonomousCar car;
    car.navigateToDestination(5);
    return 0;
}
